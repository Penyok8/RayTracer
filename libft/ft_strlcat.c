/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 16:39:03 by ozhovnuv          #+#    #+#             */
/*   Updated: 2016/12/02 17:26:37 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t len;
	size_t j;

	j = -1;
	len = 0;
	while (dst[len] && len < size)
		len++;
	if (size > len)
	{
		while (src[++j] && (len + j + 1) < size)
			dst[len + j] = src[j];
		dst[len + j] = '\0';
	}
	return (len + ft_strlen(src));
}
