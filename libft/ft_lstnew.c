/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 13:12:52 by ozhovnuv          #+#    #+#             */
/*   Updated: 2016/12/07 13:12:54 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*elem;

	elem = (t_list*)malloc(sizeof(t_list));
	if (content == NULL)
	{
		elem->content = NULL;
		elem->content_size = 0;
	}
	else
	{
		if (elem == NULL)
			return (NULL);
		elem->content = (t_list*)malloc(content_size);
		if (elem->content == NULL)
		{
			free(elem);
			return (NULL);
		}
		ft_memcpy(elem->content, content, content_size);
		elem->content_size = content_size;
	}
	elem->next = NULL;
	return (elem);
}
