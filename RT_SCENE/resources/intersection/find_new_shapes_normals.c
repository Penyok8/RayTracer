/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_new_shapes_normals.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvasin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 15:09:39 by yvasin            #+#    #+#             */
/*   Updated: 2017/07/12 15:09:40 by yvasin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rt.h"

t_vector		normal_disk(t_ray *ray, void *obj)
{
	t_disk		*disk;
	t_vector	norm;

	disk = (t_disk *)(obj);
	norm = disk->normal;
	if (find_cos_vectors(&norm, &ray->dir) < 0)
		norm = vector_scale(&norm, -1);
	return (norm);
}

t_vector		normal_tube(t_ray *ray, void *obj)
{
	t_tube		*tube;
	t_vector	norm;
	t_vector	c;
	double		temp;

	tube = (t_tube *)(obj);
	norm = vector_sub(&ray->start, &tube->pos);
	temp = vector_dot(&norm, &tube->rot);
	c = vector_scale(&tube->rot, temp);
	norm = vector_sub(&norm, &c);
	norm = normalize(&norm);
	return (norm);
}

t_vector		normal_ellipse(t_ray *ray, void *obj)
{
	t_ellipse	*ellipse;
	t_vector	norm;
	t_vector	temp;

	ellipse = (t_ellipse *)obj;
	temp = vector_sub(&ray->start, &ellipse->position);
	norm.x = 2.0 * temp.x / (ellipse->size.x * ellipse->size.x);
	norm.y = 2.0 * temp.y / (ellipse->size.y * ellipse->size.y);
	norm.z = 2.0 * temp.z / (ellipse->size.z * ellipse->size.z);
	norm = normalize(&norm);
	return (norm);
}

t_vector		normal_triangle(t_ray *ray, void *obj)
{
	t_triangle	*tr;
	t_vector	norm;

	tr = (t_triangle *)(obj);
	norm = tr->normal;
	if (find_cos_vectors(&norm, &ray->dir) < 0)
		norm = vector_scale(&norm, -1);
	return (norm);
}
