/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libvector2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <ozhovnuv@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/02 13:30:10 by ozhovnuv          #+#    #+#             */
/*   Updated: 2017/07/02 14:15:24 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double		find_cos_vectors(t_vector *v1, t_vector *v2)
{
	double cos;

	cos = (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z) /
		(sqrt(v1->x * v1->x + v1->y * v1->y + v1->z * v1->z)
			* sqrt(v2->x * v2->x + v2->y * v2->y + v2->z * v2->z));
	return (cos);
}

t_vector	v_cross(t_vector a, t_vector b)
{
	t_vector new;

	new.x = a.y * b.z - a.z * b.y;
	new.y = a.z * b.x - a.x * b.z;
	new.z = a.x * b.y - a.y * b.x;
	return (new);
}

t_vector	v_scale(t_vector a, double b)
{
	t_vector new;

	new.x = a.x * b;
	new.y = a.y * b;
	new.z = a.z * b;
	return (new);
}

double		v_dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vector	v_normalize(t_vector a)
{
	t_vector new;

	new.x = a.x / v_magnitude(a);
	new.y = a.y / v_magnitude(a);
	new.z = a.z / v_magnitude(a);
	return (new);
}
