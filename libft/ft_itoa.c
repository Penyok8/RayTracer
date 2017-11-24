/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 19:43:58 by ozhovnuv          #+#    #+#             */
/*   Updated: 2016/12/04 19:44:01 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_numlen(long int nb)
{
	int len;

	len = 1;
	while (nb > 9)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

char		*ft_itoa(int n)
{
	long int	nb;
	char		*str;
	int			sign;
	int			len;

	sign = 0;
	nb = n;
	if (n < 0)
		sign = 1;
	if (n < 0)
		nb = -nb;
	len = ft_numlen(nb) + sign;
	str = (char*)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	str[len--] = '\0';
	while (len > -1)
	{
		str[len--] = (nb % 10) + 48;
		nb /= 10;
	}
	if (sign == 1)
		str[0] = '-';
	return (str);
}
