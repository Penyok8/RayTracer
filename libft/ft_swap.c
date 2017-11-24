/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 07:51:38 by ozhovnuv          #+#    #+#             */
/*   Updated: 2016/12/11 07:51:40 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_swap(int *a, int *b)
{
	int buf;

	buf = *a;
	*a = *b;
	*b = buf;
}

void	ft_swapd(double *a, double *b)
{
	double buf;

	buf = *a;
	*a = *b;
	*b = buf;
}
