/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 15:21:09 by ozhovnuv          #+#    #+#             */
/*   Updated: 2016/12/03 15:21:14 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (s != NULL)
	{
		i = 0;
		str = (char*)malloc(len + 1);
		if (str != NULL)
		{
			while (i < len)
			{
				str[i] = s[i + start];
				i++;
			}
			str[i] = '\0';
			return (str);
		}
	}
	return (NULL);
}
