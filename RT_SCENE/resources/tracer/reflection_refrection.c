/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection_refrection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <ozhovnuv@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 16:49:35 by ozhovnuv          #+#    #+#             */
/*   Updated: 2017/07/10 19:40:48 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rt.h"

t_vector	reflected_ray(t_vector *dir, t_vector *norm)
{
	t_vector	res;
	t_vector	tmp;
	double		coef;

	coef = vector_dot(dir, norm);
	coef *= -1;
	tmp = vector_scale(norm, 2 * coef);
	res = vector_add(&tmp, dir);
	res = normalize(&res);
	return (res);
}

t_vector	refrected_ray(t_vector *dir, t_vector *norm, double ior)
{
	double		cos_i;
	t_vector	et;
	t_vector	n;
	t_vector	res;

	et.x = 1;
	et.y = ior;
	cos_i = vector_dot(dir, norm) > 1 ? 1 : vector_dot(dir, norm);
	cos_i = vector_dot(dir, norm) < -1 ? -1 : vector_dot(dir, norm);
	n = vector_scale(norm, 1);
	if (cos_i < 0)
		cos_i = -cos_i;
	else
	{
		n = vector_scale(norm, -1);
		ft_swapd(&et.x, &et.y);
	}
	et.z = et.x / et.y;
	res = refr_addit(&et, cos_i, dir, &n);
	return (res);
}

t_vector	refr_addit(t_vector *et, double cos_i, t_vector *dir, t_vector *n)
{
	double		k;
	t_vector	res;
	t_vector	d;
	t_vector	w;

	k = 1 - ((et->z * et->z) * (1 - (cos_i * cos_i)));
	if (k < 0)
		res = v_new_data(0, 0, 0);
	else
	{
		d = vector_scale(dir, et->z);
		w = vector_scale(n, ((et->z * cos_i) - sqrt(k)));
		res = vector_add(&d, &w);
	}
	res = normalize(&res);
	return (res);
}
