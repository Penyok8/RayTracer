/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_tube.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <ozhovnuv@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/02 11:31:25 by ozhovnuv          #+#    #+#             */
/*   Updated: 2017/07/03 14:51:21 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rt.h"

t_vector		tube_abc(t_ray *ray, t_tube *tube, t_vector *dist)
{
	t_vector	abc;

	abc.x = vector_dot(&ray->dir, &ray->dir)
	- pow(vector_dot(&ray->dir, &tube->rot), 2);
	abc.y = 2 * (vector_dot(&ray->dir, dist)
		- (vector_dot(&ray->dir, &tube->rot) * vector_dot(dist, &tube->rot)));
	abc.z = vector_dot(dist, dist) - pow(vector_dot(dist, &tube->rot), 2)
	- pow(tube->radius, 2);
	return (abc);
}

int				intersect_tube(t_ray *ray, void *obj, t_main *main, double d)
{
	t_vector	abc;
	t_tube		*c;
	t_vector	dist;
	double		disc;
	double		t;

	c = (t_tube *)(obj);
	dist = v_diff(ray->start, c->bottom);
	abc = tube_abc(ray, c, &dist);
	disc = abc.y * abc.y - 4 * abc.x * abc.z;
	if (disc < 0)
		return (0);
	disc = sqrt(disc);
	if (!(t = min_p((-abc.y + disc) / (2 * abc.x),
		(-abc.y - disc) / (2 * abc.x), main)))
		return (0);
	abc = v_sum(ray->start, v_scale(ray->dir, t));
	if (v_dot(c->rot, v_diff(abc, c->bottom)) < 0 ||
		v_dot(c->rot, v_diff(abc, c->top)) > 0)
		return (0);
	if (t < 0.01 || t > main->t)
		return (0);
	main->t = t - 0.01;
	return (main->t < d ? 1 : 0);
}
