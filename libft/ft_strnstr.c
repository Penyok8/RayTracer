/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 17:51:24 by ozhovnuv          #+#    #+#             */
/*   Updated: 2016/12/01 19:29:26 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t i;
	size_t j;

	i = 0;
	if (little[0] == '\0')
		return ((char*)big);
	while (big[i])
	{
		j = 0;
		while ((big[j] == little[j + i] || little[j]) && (j + i) < len)
		{
			if (little[j] != big[j + i])
				break ;
			else if (little[j + 1] == '\0')
				return ((char*)big + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
