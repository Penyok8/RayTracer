/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 13:37:42 by ozhovnuv          #+#    #+#             */
/*   Updated: 2016/12/03 13:37:44 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	int		i;

	i = -1;
	if (s != NULL)
	{
		str = (char*)malloc(ft_strlen(s) + 1);
		if (str != NULL)
		{
			while (s[++i])
				str[i] = f(i, s[i]);
			str[i] = '\0';
			return (str);
		}
	}
	return (NULL);
}
