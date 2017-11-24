/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 18:02:35 by ozhovnuv          #+#    #+#             */
/*   Updated: 2016/12/07 18:02:39 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *fresh;
	t_list *temp;

	if (lst)
		temp = f(lst);
	if (lst == NULL)
		return (NULL);
	fresh = temp;
	while (lst->next)
	{
		lst = lst->next;
		fresh->next = f(lst);
		if (!fresh->next)
			return (NULL);
		fresh = fresh->next;
	}
	return (temp);
}
