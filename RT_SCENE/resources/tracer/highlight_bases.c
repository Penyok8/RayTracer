/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   highlight_bases.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvasin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 20:52:49 by yvasin            #+#    #+#             */
/*   Updated: 2017/07/10 20:52:50 by yvasin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rt.h"

t_color		color_scale(t_color color, double factor)
{
	t_color res;

	res.r = (unsigned char)color.r * factor;
	res.g = (unsigned char)color.g * factor;
	res.b = (unsigned char)color.b * factor;
	res.a = (unsigned char)color.a * factor;
	return (res);
}

t_color		color_add(t_color c1, t_color c2)
{
	t_color color;

	color.r = c1.r + c2.r;
	color.g = c1.g + c2.g;
	color.b = c1.b + c2.b;
	color.a = c1.a + c2.a;
	return (color);
}

t_color		highlight_obj(t_obj *obj, t_ray *ray, t_color color, t_light *light)
{
	t_vector	norm;
	t_color		color_dark;
	double		coss;

	norm = obj->find_normal(ray, obj->obj);
	coss = find_cos_vectors(&norm, &ray->dir);
	color_dark = BLACK;
	color_dark.a += (unsigned char)(230 * (1 - coss));
	if (light->type != PARALLEL_LIGHT)
	{
		color_dark.r += (255 - (unsigned char)color.r)
			* (0.9 * pow(coss, 50) + 0.1 * coss);
		color_dark.g += (255 - (unsigned char)color.g)
			* (0.9 * pow(coss, 50) + 0.1 * coss);
		color_dark.b += (255 - (unsigned char)color.b)
			* (0.9 * pow(coss, 50) + 0.1 * coss);
	}
	return (color_dark);
}

t_vector	define_bases(t_vector *dir)
{
	t_vector	v_up;

	if (dir->x >= dir->y && dir->x >= dir->z)
		v_up = v_new_data(1, 0, 0);
	if (dir->y >= dir->x && dir->y >= dir->z)
		v_up = v_new_data(0, 1, 0);
	if (dir->z >= dir->x && dir->z >= dir->y)
		v_up = v_new_data(0, 0, 1);
	return (v_up);
}

void		light_dir_ray(t_light *cur, t_ray *sh_ray)
{
	if (cur->type == PARALLEL_LIGHT)
		sh_ray->dir = cur->dir;
	else
	{
		sh_ray->dir = vector_sub(&cur->pos, &sh_ray->start);
		sh_ray->dir = normalize(&sh_ray->dir);
	}
}
