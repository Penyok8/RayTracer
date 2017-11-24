/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libvector4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <ozhovnuv@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/02 13:30:10 by ozhovnuv          #+#    #+#             */
/*   Updated: 2017/07/02 14:15:24 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double		s_cos(t_vector a, t_vector b)
{
	return (v_dot(a, b) / (v_magnitude(a) * v_magnitude(b)));
}
