/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 15:33:35 by ozhovnuv          #+#    #+#             */
/*   Updated: 2016/12/01 16:57:35 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	*dest;
	size_t			i;

	i = 0;
	str = (unsigned char*)src;
	dest = (unsigned char*)dst;
	while (i < n)
	{
		dest[i] = str[i];
		if (str[i] == (unsigned char)c)
			return (dest + i + 1);
		i++;
	}
	return (NULL);
}
