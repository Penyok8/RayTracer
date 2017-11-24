/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 22:53:48 by ozhovnuv          #+#    #+#             */
/*   Updated: 2016/12/02 23:53:51 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*s;
	size_t	i;

	i = 0;
	s = (char*)malloc(size + 1);
	if (s != NULL)
	{
		while (i <= size)
			s[i++] = '\0';
		return (s);
	}
	else
		return (NULL);
}
