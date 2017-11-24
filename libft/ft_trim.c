/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 17:44:54 by ozhovnuv          #+#    #+#             */
/*   Updated: 2017/08/21 17:44:58 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_trim(char *str)
{
	int		i;
	int		start_pos;
	int		end_pos;

	i = -1;
	start_pos = 0;
	while (str[i++])
	{
		if (str[i] > 40)
		{
			start_pos = i;
			break ;
		}
	}
	i = ft_strlen(str);
	end_pos = i + 1;
	while (i-- >= 0)
	{
		if (str[i] > 40)
		{
			end_pos = i;
			break ;
		}
	}
	return (ft_strsub(str, start_pos, end_pos - start_pos + 1));
}
