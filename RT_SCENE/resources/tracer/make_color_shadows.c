/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_color_shadows.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvasin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 20:52:49 by yvasin            #+#    #+#             */
/*   Updated: 2017/07/10 20:52:50 by yvasin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rt.h"

t_color		make_color(t_obj *obj, t_main *main, t_ray *ray)
{
	t_color		color;
	t_color		final_color;
	t_ray		shadow_ray;
	double		light_d;
	t_light		*current;

	current = main->light;
	shadow_ray = find_shadow_ray(ray, main);
	if (obj->texture != NULL
		&& (obj->transparency <= 0 || obj->reflection <= 0))
		obj->texture_obj(obj->obj, obj, shadow_ray.start);
	final_color = obj->color;
	while (current != NULL)
	{
		light_dir_ray(current, &shadow_ray);
		main->dist_to_light = vector_sub(&current->pos, &shadow_ray.start);
		main->color_obj = obj;
		make_color_shadows(shadow_ray, &final_color, current, main);
		current = current->next;
	}
	return (final_color);
}

void		make_color_shadows(t_ray ray,
	t_color *f_c, t_light *cur, t_main *main)
{
	double		light_d;
	t_vector	v_up;
	t_vector	uu;
	t_vector	vv;
	int			i;

	i = 0;
	light_d = sqrt(vector_dot(&main->dist_to_light, &main->dist_to_light));
	v_up = define_bases(&ray.dir);
	uu = v_cross(v_up, ray.dir);
	vv = v_cross(ray.dir, v_cross(v_up, ray.dir));
	while (i < main->ss_ray_iter)
	{
		if (main->ss_rays > 0)
			randomize_ray(&uu, &vv, &ray, cur);
		if (!(find_intersection(ray, main, light_d)))
			color_inter_obj(cur, ray, f_c, main);
		else
			f_c->a += 230 * cur->intensity / main->ss_ray_iter;
		i++;
	}
}

void		color_inter_obj(t_light *cur, t_ray ray, t_color *f_c, t_main *main)
{
	t_color color;

	if (cur->type == DIRECTIONAL_LIGHT &&
		acos(find_cos_vectors(&ray.dir, &cur->dir)) > cur->angle)
		f_c->a += 230 * cur->intensity / main->ss_ray_iter;
	else
	{
		color = highlight_obj(main->color_obj, &ray, *f_c, cur);
		color = color_scale(color, cur->intensity
				* ((double)1 / main->ss_ray_iter));
		*f_c = color_add(*f_c, color);
	}
}

void		randomize_ray(t_vector *uu, t_vector *vv,
						t_ray *sh_ray, t_light *cur)
{
	double		du;
	double		dv;
	t_vector	uuu;
	t_vector	vvv;

	du = rand() / (double)(RAND_MAX);
	dv = rand() / (double)(RAND_MAX);
	uuu = vector_scale(uu, (cos(5.0 * du) * 5.0));
	vvv = vector_scale(vv, (sin(5.0 * dv) * 5.0));
	set_random_dir(&uuu, &vvv, sh_ray, cur);
}

void		set_random_dir(t_vector *uuu, t_vector *vvv,
						t_ray *sh_ray, t_light *current)
{
	t_vector	o;
	t_vector	p;

	o = vector_add(uuu, vvv);
	p = vector_add(&current->pos, &o);
	sh_ray->dir = vector_sub(&p, &sh_ray->start);
	sh_ray->dir = normalize(&sh_ray->dir);
}
