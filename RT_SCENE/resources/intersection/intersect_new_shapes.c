/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_new_shapes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <ozhovnuv@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/02 11:31:25 by ozhovnuv          #+#    #+#             */
/*   Updated: 2017/07/03 14:51:21 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rt.h"

t_color	count_param(t_ray *ray, t_vector dist, t_ellipse *el,
							t_color coefs)
{
	coefs.r = (ray->dir.x * ray->dir.x) / (el->size.x * el->size.x) +
				(ray->dir.y * ray->dir.y) / (el->size.y * el->size.y) +
				(ray->dir.z * ray->dir.z) / (el->size.z * el->size.z);
	coefs.g = (2.0 * dist.x * ray->dir.x) / (el->size.x * el->size.x) +
				(2.0 * dist.y * ray->dir.y) / (el->size.y * el->size.y) +
				(2.0 * dist.z * ray->dir.z) / (el->size.z * el->size.z);
	coefs.b = (dist.x * dist.x) / (el->size.x * el->size.x) +
				(dist.y * dist.y) / (el->size.y * el->size.y) +
				(dist.z * dist.z) / (el->size.z * el->size.z) - 1.0;
	coefs.a = ((coefs.g * coefs.g) - (4.0 * coefs.r * coefs.b));
	return (coefs);
}

int		intersect_ellipse(t_ray *ray, void *obj, t_main *main, double d)
{
	t_ellipse	*el;
	t_color		coefs;
	t_vector	dist;
	t_vector	tt;
	int			ret;

	ret = 0;
	el = (t_ellipse *)obj;
	dist = vector_sub(&ray->start, &el->position);
	coefs = count_param(ray, dist, el, coefs);
	if (coefs.a < 0.0)
		return (0);
	coefs.a = sqrt(coefs.a);
	tt.x = (-coefs.g + coefs.a) / (2.0 * coefs.r);
	tt.y = (-coefs.g - coefs.a) / (2.0 * coefs.r);
	(tt.x > 0.001) && (tt.x < main->t) ? ret = 1 : 0;
	(tt.x > 0.001) && (tt.x < main->t) ? main->t = tt.x : 0;
	(tt.y > 0.001) && (tt.y < main->t) ? ret = 1 : 0;
	(tt.y > 0.001) && (tt.y < main->t) ? main->t = tt.y : 0;
	main->t -= 0.01;
	if (main->t > d)
		return (0);
	return (ret);
}

int		triangle_uv(t_triangle *tr, t_ray *ray, double inv_det, double *t)
{
	double		u;
	double		v;
	t_vector	tvec;
	t_vector	qvec;

	tvec = v_diff(ray->start, tr->v0);
	u = v_dot(tvec, v_cross(ray->dir, tr->e2)) * inv_det;
	if (u < 0 || u > 1)
		return (0);
	qvec = v_cross(tvec, tr->e1);
	v = v_dot(ray->dir, qvec) * inv_det;
	if (v < 0 || u + v > 1)
		return (0);
	*t = v_dot(tr->e2, qvec) * inv_det;
	return (1);
}

int		intersect_triangle(t_ray *ray, void *obj, t_main *main, double d)
{
	double		det;
	t_triangle	*tr;
	double		t;

	tr = (t_triangle *)(obj);
	det = v_dot(tr->e1, v_cross(ray->dir, tr->e2));
	if (fabs(det) < 0.001 || triangle_uv(tr, ray, (1.0 / det), &t) == 0)
		return (0);
	if (t < 0.01 || t > main->t)
		return (0);
	main->t = t - 0.1;
	if (main->t > d)
		return (0);
	return (1);
}

int		intersect_disk(t_ray *ray, void *obj, t_main *main, double d)
{
	double		denom;
	t_vector	pl;
	t_disk		*disk;
	double		t;

	disk = (t_disk *)(obj);
	disk->normal = v_normalize(disk->normal);
	denom = vector_dot(&disk->normal, &ray->dir);
	if (fabs(denom) < 0.001)
		return (0);
	pl = vector_sub(&disk->pos, &ray->start);
	t = vector_dot(&pl, &disk->normal) / denom;
	if (t > 0.001 && t < main->t)
	{
		pl = v_diff(disk->pos, v_sum(ray->start, v_scale(ray->dir, t)));
		if (v_magnitude(pl) <= disk->radius && v_magnitude(pl) >
			disk->in_radius)
		{
			main->t = t - 0.1;
			if (main->t > d)
				return (0);
			return (1);
		}
	}
	return (0);
}
