/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bsort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 08:00:37 by ozhovnuv          #+#    #+#             */
/*   Updated: 2016/12/12 16:03:30 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bsort(int *mas, int len)
{
	int flag;
	int	i;

	flag = 1;
	while (flag == 1)
	{
		flag = 0;
		i = 0;
		while (i < len)
		{
			if (mas[i] > mas[i + 1])
			{
				ft_swap(&mas[i], &mas[i + 1]);
				flag = 1;
			}
			i++;
		}
	}
}
