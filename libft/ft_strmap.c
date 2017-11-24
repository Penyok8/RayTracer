/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 12:54:48 by ozhovnuv          #+#    #+#             */
/*   Updated: 2016/12/03 12:54:55 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
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
				str[i] = f(s[i]);
			str[i] = '\0';
			return (str);
		}
	}
	return (NULL);
}
