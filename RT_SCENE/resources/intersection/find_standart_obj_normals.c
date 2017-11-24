/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_standart_obj_normals.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvasin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 15:09:39 by yvasin            #+#    #+#             */
/*   Updated: 2017/07/12 15:09:40 by yvasin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rt.h"

t_vector		normal_cylinder(t_ray *ray, void *obj)
{
	t_cylinder	*cyl;
	t_vector	norm;
	t_vector	c;
	double		temp;

	cyl = (t_cylinder *)(obj);
	norm = vector_sub(&ray->start, &cyl->pos);
	temp = vector_dot(&norm, &cyl->rot);
	c = vector_scale(&cyl->rot, temp);
	norm = vector_sub(&norm, &c);
	norm = normalize(&norm);
	return (norm);
}

t_vector		normal_lcylinder(t_ray *ray, void *obj)
{
	t_lcylinder	*cyl;
	t_vector	norm;
	t_vector	c;
	double		temp;

	cyl = (t_lcylinder *)(obj);
	if (fabs(v_dot(cyl->rot, v_diff(ray->start, cyl->bottom))) < 0.1)
		return (v_scale(cyl->rot, -1));
	else if (fabs(v_dot(cyl->rot, v_diff(ray->start, cyl->top))) < 0.1)
		return (cyl->rot);
	norm = vector_sub(&ray->start, &cyl->bottom);
	temp = vector_dot(&norm, &cyl->rot);
	c = vector_scale(&cyl->rot, temp);
	norm = vector_sub(&norm, &c);
	norm = normalize(&norm);
	return (norm);
}

t_vector		normal_sphere(t_ray *ray, void *obj)
{
	t_sphere	*sphere;
	t_vector	norm;

	sphere = (t_sphere *)(obj);
	norm = vector_sub(&ray->start, &sphere->centre);
	norm = normalize(&norm);
	return (norm);
}

t_vector		normal_plane(t_ray *ray, void *obj)
{
	t_plane		*plane;
	t_vector	norm;

	plane = (t_plane *)(obj);
	norm = plane->normal;
	if (find_cos_vectors(&norm, &ray->dir) < 0)
		norm = vector_scale(&norm, -1);
	return (norm);
}

t_vector		normal_cone(t_ray *ray, void *obj)
{
	t_cone		*cone;
	t_vector	norm;
	t_vector	c;
	double		temp;

	cone = (t_cone *)(obj);
	norm = vector_sub(&ray->start, &cone->pos);
	temp = vector_dot(&norm, &cone->rot);
	c = vector_scale(&cone->rot, temp);
	c = vector_scale(&c, (1 + pow(tan(cone->angle), 2)));
	norm = vector_sub(&norm, &c);
	norm = normalize(&norm);
	return (norm);
}
