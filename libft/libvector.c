/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libvector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <ozhovnuv@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 20:35:23 by ozhovnuv          #+#    #+#             */
/*   Updated: 2017/07/02 13:29:49 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vector	vector_sub(t_vector *v1, t_vector *v2)
{
	t_vector res;

	res.x = v1->x - v2->x;
	res.y = v1->y - v2->y;
	res.z = v1->z - v2->z;
	return (res);
}

t_vector	vector_scale(t_vector *v, double scale)
{
	t_vector res;

	res.x = v->x * scale;
	res.y = v->y * scale;
	res.z = v->z * scale;
	return (res);
}

t_vector	vector_add(t_vector *v1, t_vector *v2)
{
	t_vector res;

	res.x = v1->x + v2->x;
	res.y = v1->y + v2->y;
	res.z = v1->z + v2->z;
	return (res);
}

t_vector	normalize(t_vector *vector)
{
	t_vector	norm;
	double		length;

	length = sqrt(vector_dot(vector, vector));
	norm = vector_scale(vector, 1 / length);
	return (norm);
}

double		vector_dot(t_vector *v1, t_vector *v2)
{
	double res;

	res = (v1->x * v2->x) + (v1->y * v2->y) + (v1->z * v2->z);
	return (res);
}
