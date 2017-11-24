/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_lim_cylinder.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <ozhovnuv@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/02 11:31:25 by ozhovnuv          #+#    #+#             */
/*   Updated: 2017/07/03 14:51:21 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rt.h"

double		min_p(double t1, double t2, t_main *main)
{
	double b;

	if (((b = fmin(t1, t2)) > 0.1 && b < main->t) ||
		((b = fmax(t1, t2)) > 0.1 && b < main->t))
		return (b - 0.01);
	return (0);
}

t_vector	lcyl_abc(t_ray *ray, t_lcylinder *cyl, t_vector *dist)
{
	t_vector abc;

	abc.x = vector_dot(&ray->dir, &ray->dir)
		- pow(vector_dot(&ray->dir, &cyl->rot), 2);
	abc.y = 2 * (vector_dot(&ray->dir, dist)
	- (vector_dot(&ray->dir, &cyl->rot) * vector_dot(dist, &cyl->rot)));
	abc.z = vector_dot(dist, dist) - pow(vector_dot(dist, &cyl->rot), 2)
		- pow(cyl->radius, 2);
	return (abc);
}

double		intr_cap(t_vector pos, t_vector normal, double radius, t_ray *ray)
{
	double		denom;
	t_vector	pl;
	double		t;
	t_vector	point_pos;

	denom = v_dot(normal, ray->dir);
	if (fabs(denom) > 0.001)
	{
		pl = v_diff(pos, ray->start);
		t = v_dot(pl, normal) / denom;
		if (t > 0.01)
		{
			point_pos = v_diff(pos, v_sum(ray->start, v_scale(ray->dir, t)));
			if (v_magnitude(point_pos) <= radius)
				return (t);
		}
	}
	return (INFINITY);
}

double		lcyl_caps(double t, t_lcylinder *c, t_ray *ray)
{
	double	t_caps;

	t_caps = intr_cap(c->top, c->rot, c->radius, ray);
	t = fmin(t, t_caps);
	t_caps = intr_cap(c->bottom, c->rot, c->radius, ray);
	return (fmin(t, t_caps));
}

int			intersect_lcylinder(t_ray *ray, void *obj, t_main *main, double d)
{
	t_vector	abc;
	t_vector	dist;
	double		disc;
	double		t;

	((t_lcylinder *)(obj))->rot = v_normalize(((t_lcylinder *)(obj))->rot);
	dist = v_diff(ray->start, ((t_lcylinder *)(obj))->bottom);
	abc = lcyl_abc(ray, ((t_lcylinder *)(obj)), &dist);
	disc = sqrt(abc.y * abc.y - 4 * abc.x * abc.z);
	if (disc * disc < 0)
		return (0);
	if ((t = min_p((-abc.y + disc) / (2 * abc.x), (-abc.y - disc) /
		(2 * abc.x), main)))
	{
		abc = v_sum(ray->start, v_scale(ray->dir, t));
		if (v_dot(((t_lcylinder *)(obj))->rot,
			v_diff(abc, ((t_lcylinder *)(obj))->bottom)) < 0 ||
			v_dot(((t_lcylinder *)(obj))->rot,
			v_diff(abc, ((t_lcylinder *)(obj))->top)) > 0)
			t = INFINITY;
	}
	if ((t = lcyl_caps(t, ((t_lcylinder *)(obj)), ray)) < 0.01 || t > main->t)
		return (0);
	main->t = t - 0.01;
	return (main->t < d ? 1 : 0);
}
