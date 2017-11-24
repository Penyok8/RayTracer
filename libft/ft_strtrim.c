/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 17:34:01 by ozhovnuv          #+#    #+#             */
/*   Updated: 2016/12/03 19:37:51 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*str;
	int		st;
	int		end;

	if (s == NULL)
		return (NULL);
	st = 0;
	while (s[st] == ' ' || s[st] == '\n' || s[st] == '\t')
		st++;
	end = ft_strlen(s);
	if (st == end)
		return (ft_strnew(0));
	while (s[end - 1] == ' ' || s[end - 1] == '\n' || s[end - 1] == '\t')
		end--;
	str = ft_strsub(s, st, end - st);
	if (str == NULL)
		return (NULL);
	return (str);
}
