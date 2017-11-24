/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 16:03:34 by ozhovnuv          #+#    #+#             */
/*   Updated: 2016/12/01 18:45:29 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	int i;
	int j;

	i = 0;
	if (little[0] == '\0')
		return ((char*)big);
	while (big[i])
	{
		j = 0;
		while (big[j] == little[j + i] || little[j])
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
