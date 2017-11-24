/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 16:07:06 by ozhovnuv          #+#    #+#             */
/*   Updated: 2016/11/30 16:27:59 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*str;
	int				i;

	str = (unsigned char*)b;
	i = 0;
	while (i < (int)len)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return (str);
}
