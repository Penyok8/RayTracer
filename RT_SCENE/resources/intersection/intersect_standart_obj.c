/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_standart_obj.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <ozhovnuv@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/02 11:31:25 by ozhovnuv          #+#    #+#             */
/*   Updated: 2017/07/03 14:51:21 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rt.h"

int				intersect_sphere(t_ray *ray, void *obj, t_main *main, double d)
{
	t_vector	dist;
	t_vector	ab;
	t_vector	tt;
	t_sphere	*sphere;
	int			ret;

	ret = 0;
	sphere = (t_sphere *)(obj);
	dist = vector_sub(&sphere->centre, &ray->start);
	ab.x = vector_dot(&ray->dir, &dist);
	ab.y = ab.x * ab.x - vector_dot(&dist, &dist) + pow(sphere->radius, 2);
	if (ab.y < 0.0)
		return (0);
	tt.x = ab.x - sqrt(ab.y);
	tt.y = ab.x + sqrt(ab.y);
	(tt.x > 0.001) && (tt.x < main->t) ? ret = 1 : 0;
	(tt.x > 0.001) && (tt.x < main->t) ? main->t = tt.x : 0;
	(tt.y > 0.001) && (tt.y < main->t) ? ret = 1 : 0;
	(tt.y > 0.001) && (tt.y < main->t) ? main->t = tt.y : 0;
	main->t -= 0.01;
	if (main->t > d)
		return (0);
	return (ret);
}

t_vector		cone_abc(t_ray *ray, t_cone *cone, t_vector *dist)
{
	t_vector	abc;

	abc.x = vector_dot(&ray->dir, &ray->dir)
	- (1 + pow(tan(cone->angle), 2))
	* pow(vector_dot(&ray->dir, &cone->rot), 2);
	abc.y = 2 * (vector_dot(&ray->dir, dist)
	- (1 + pow(tan(cone->angle), 2)) * (vector_dot(&ray->dir, &cone->rot)
	* vector_dot(dist, &cone->rot)));
	abc.z = vector_dot(dist, dist)
	- (1 + pow(tan(cone->angle), 2)) * pow(vector_dot(dist, &cone->rot), 2);
	return (abc);
}

int				intersect_cone(t_ray *ray, void *obj, t_main *main, double d)
{
	t_vector	dist;
	t_vector	abc;
	t_vector	t;
	double		discr;
	int			ret;

	ret = 0;
	dist = vector_sub(&((t_cone *)(obj))->pos, &ray->start);
	((t_cone *)(obj))->rot = normalize(&((t_cone *)(obj))->rot);
	abc = cone_abc(ray, ((t_cone *)(obj)), &dist);
	discr = abc.y * abc.y - 4 * abc.x * abc.z;
	if (discr < 0)
		return (ret);
	t.x = (abc.y - sqrt(discr)) / (2 * abc.x);
	t.y = (abc.y + sqrt(discr)) / (2 * abc.x);
	(t.x > 0.001) && (t.x < main->t) ? ret = 1 : 0;
	(t.x > 0.001) && (t.x < main->t) ? main->t = t.x : 0;
	(t.y > 0.001) && (t.y < main->t) ? ret = 1 : 0;
	(t.y > 0.001) && (t.y < main->t) ? main->t = t.y : 0;
	main->t -= 0.01;
	if (main->t > d)
		return (0);
	return (ret);
}

int				intersect_plane(t_ray *ray, void *obj, t_main *main, double d)
{
	double		denom;
	t_vector	pl;
	t_plane		*plane;
	double		t;

	plane = (t_plane *)(obj);
	denom = vector_dot(&plane->normal, &ray->dir);
	if (fabs(denom) > 0.001)
	{
		pl = vector_sub(&plane->pos, &ray->start);
		t = vector_dot(&pl, &plane->normal) / denom;
		if (t > 0.001 && t < main->t)
		{
			pl = v_diff(plane->pos, v_sum(ray->start, v_scale(ray->dir, t)));
			if (v_magnitude(pl) >= plane->sphere_radius)
			{
				main->t = t - 0.1;
				if (main->t > d)
					return (0);
				return (1);
			}
		}
	}
	return (0);
}
