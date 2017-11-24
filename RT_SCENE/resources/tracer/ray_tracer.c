/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvasin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 20:52:49 by yvasin            #+#    #+#             */
/*   Updated: 2017/07/10 20:52:50 by yvasin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rt.h"

t_color		cast_ray(t_ray ray, int depth, t_main *main)
{
	t_color		final_color;
	t_color		new_color1;
	t_color		new_color2;
	t_obj		*current_obj;

	new_color1 = BLACK;
	new_color2 = BLACK;
	if (depth > MAX_DEPTH)
		return (BLACK);
	if ((current_obj = find_intersection(ray, main, INFINITY)) != NULL)
	{
		main->temp_t = main->t;
		final_color = make_color(current_obj, main, &ray);
	}
	else
		return (BLACK);
	if (current_obj->reflection > 0)
		new_color1 = reflection_make(&ray, main, depth, current_obj);
	if (current_obj->transparency > 0 && current_obj->refrection > 1.0)
		new_color2 = refraction_make(&ray, main, depth, current_obj);
	final_color = color_scale(final_color,
		1 - fmin(1, (current_obj->transparency + current_obj->reflection)));
	final_color = color_add(final_color, color_add(new_color1, new_color2));
	return (final_color);
}

t_color		reflection_make(t_ray *ray, t_main *main, int depth, t_obj *obj)
{
	t_ray		refl_ray;
	t_vector	norm;
	t_color		color;

	main->t = main->temp_t;
	refl_ray = find_shadow_ray(ray, main);
	norm = obj->find_normal(&refl_ray, obj->obj);
	refl_ray.dir = reflected_ray(&ray->dir, &norm);
	color = cast_ray(refl_ray, depth + 1, main);
	color = color_scale(color, obj->reflection);
	return (color);
}

t_color		refraction_make(t_ray *ray, t_main *main, int depth, t_obj *obj)
{
	t_ray		refl_ray;
	t_vector	norm;
	t_color		color;

	main->t = main->temp_t;
	main->t += 1;
	refl_ray = find_shadow_ray(ray, main);
	norm = obj->find_normal(&refl_ray, obj->obj);
	refl_ray.dir = refrected_ray(&ray->dir, &norm, obj->refrection);
	color = cast_ray(refl_ray, depth + 1, main);
	color = color_scale(color, obj->transparency);
	return (color);
}

t_obj		*find_intersection(t_ray ray, t_main *main, double light_distance)
{
	t_obj	*current;
	t_obj	*res;

	main->t = INFINITY;
	current = main->obj;
	res = NULL;
	while (current != NULL)
	{
		if (current->intersection(&ray,
			current->obj, main, light_distance) == 1)
			res = current;
		current = current->next;
	}
	return (res);
}

t_ray		find_shadow_ray(t_ray *ray, t_main *main)
{
	t_ray		shadow_ray;
	t_vector	scaled;
	t_vector	new_start;

	scaled = vector_scale(&ray->dir, main->t);
	new_start = vector_add(&ray->start, &scaled);
	shadow_ray.start = new_start;
	return (shadow_ray);
}
