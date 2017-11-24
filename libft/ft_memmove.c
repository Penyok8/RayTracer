/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 17:27:21 by ozhovnuv          #+#    #+#             */
/*   Updated: 2016/11/30 21:47:27 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*str;
	char	*dest;
	size_t	i;

	i = 0;
	str = (char*)src;
	dest = (char*)dst;
	if (src < dst)
		while ((int)--len >= 0)
			dest[len] = str[len];
	else
		while (i < len)
		{
			dest[i] = str[i];
			i++;
		}
	return (dest);
}
