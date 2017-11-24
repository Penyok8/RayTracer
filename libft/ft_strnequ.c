/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 15:00:18 by ozhovnuv          #+#    #+#             */
/*   Updated: 2016/12/03 15:00:19 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t i;

	i = 0;
	if (s1 != NULL && s2 != NULL)
	{
		while (s1[i] && s2[i] && i < n)
		{
			if (s1[i] != s2[i])
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}
