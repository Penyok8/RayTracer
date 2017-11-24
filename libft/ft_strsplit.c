/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 22:13:37 by ozhovnuv          #+#    #+#             */
/*   Updated: 2016/12/05 22:13:42 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	min_str_len(char *s, char c)
{
	size_t len;

	len = 0;
	while (s[len] != c && s[len])
		len++;
	return (len);
}

static size_t	str_len(char *s, char c)
{
	size_t	len;
	int		i;

	i = 0;
	len = 0;
	while (s[i])
	{
		if ((s[i] != c && s[i - 1] == c) || (i == 0 && s[0] != c))
			len++;
		i++;
	}
	return (len);
}

static char		**freesher(char **str, int len)
{
	int i;

	i = 0;
	while (i < len)
		free(str[i++]);
	free(str);
	return (NULL);
}

char			**ft_strsplit(char *s, char c)
{
	char	**str;
	int		i;
	int		k;

	k = -1;
	i = 0;
	if (s == NULL)
		return (NULL);
	str = (char**)malloc(sizeof(char*) * (str_len(s, c) + 1));
	if (str == NULL)
		return (NULL);
	while (s[++k])
	{
		if ((s[k] != c && s[k - 1] == c) || (k == 0 && s[0] != c))
		{
			str[i] = ft_strsub(s, k, min_str_len(s + k, c));
			if (str[i] == NULL)
				return (freesher(str, i));
			i++;
		}
	}
	str[i] = 0;
	return (str);
}
