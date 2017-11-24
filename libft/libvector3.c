/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libvector3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <ozhovnuv@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/02 13:30:10 by ozhovnuv          #+#    #+#             */
/*   Updated: 2017/07/02 14:15:24 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		v_data(t_vector *v, double x, double y, double z)
{
	v->x = x;
	v->y = y;
	v->z = z;
}

t_vector	v_new_data(double x, double y, double z)
{
	t_vector new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

double		v_magnitude(t_vector a)
{
	return (sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2)));
}

t_vector	v_sum(t_vector a, t_vector b)
{
	t_vector new;

	new.x = a.x + b.x;
	new.y = a.y + b.y;
	new.z = a.z + b.z;
	return (new);
}

t_vector	v_diff(t_vector a, t_vector b)
{
	t_vector new;

	new.x = a.x - b.x;
	new.y = a.y - b.y;
	new.z = a.z - b.z;
	return (new);
}
