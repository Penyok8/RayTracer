/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <ozhovnuv@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/02 11:31:25 by ozhovnuv          #+#    #+#             */
/*   Updated: 2017/07/03 14:51:21 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rt.h"

t_vector		cyl_abc(t_ray *ray, t_cylinder *cyl, t_vector *dist)
{
	t_vector	abc;

	abc.x = vector_dot(&ray->dir, &ray->dir)
		- pow(vector_dot(&ray->dir, &cyl->rot), 2);
	abc.y = 2 * (vector_dot(&ray->dir, dist)
	- (vector_dot(&ray->dir, &cyl->rot) * vector_dot(dist, &cyl->rot)));
	abc.z = vector_dot(dist, dist) - pow(vector_dot(dist, &cyl->rot), 2)
		- pow(cyl->radius, 2);
	return (abc);
}

int				intersect_cylinder(t_ray *ray, void *obj, t_main *main,
	double d)
{
	t_vector	dist;
	t_vector	abc;
	t_vector	t;
	double		discr;
	int			ret;

	ret = 0;
	dist = vector_sub(&((t_cylinder *)(obj))->pos, &ray->start);
	((t_cylinder *)(obj))->rot = normalize(&((t_cylinder *)(obj))->rot);
	abc = cyl_abc(ray, ((t_cylinder *)(obj)), &dist);
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
