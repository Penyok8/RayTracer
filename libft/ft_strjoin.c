/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 15:49:29 by ozhovnuv          #+#    #+#             */
/*   Updated: 2016/12/03 15:49:30 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*str;
	int		len;

	if (s1 != NULL && s2 != NULL)
	{
		len = ft_strlen(s1);
		str = (char*)malloc(len + ft_strlen(s2) + 1);
		if (str != NULL)
		{
			i = 0;
			ft_strcpy(str, s1);
			while (s2[i])
			{
				str[i + len] = s2[i];
				i++;
			}
			str[i + len] = '\0';
			return (str);
		}
	}
	return (NULL);
}
