/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <ozhovnuv@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 14:27:06 by ozhovnuv          #+#    #+#             */
/*   Updated: 2017/01/20 20:38:04 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	det_nl(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 10)
			return (i);
		i++;
	}
	return (-1);
}

static int	ad_inf(t_lst *el)
{
	char	buff[BUFF_SIZE + 1];
	int		read_size;
	char	*temp;

	read_size = read(el->fd, buff, BUFF_SIZE);
	if (read_size == -1 || buff[0] == '\0')
		return (-1);
	buff[read_size] = '\0';
	if (read_size < BUFF_SIZE)
		el->eof = 0;
	if (read_size != 0 && el->cont != NULL)
	{
		temp = ft_strjoin(el->cont, buff);
		ft_memdel((void **)&(el->cont));
		el->cont = ft_strdup(temp);
		ft_memdel((void **)&(temp));
	}
	if (read_size != 0 && el->cont == NULL)
	{
		el->cont = ft_strnew((size_t)(read_size));
		el->cont = ft_strcat(el->cont, buff);
	}
	if (det_nl(el->cont) == -1 && el->eof == 1)
		return (ad_inf(el));
	return (0);
}

static int	check_cont(t_lst *el, char **line)
{
	int		nl;
	char	*temp;

	if (((el->cont == NULL && el->eof == 1) || (el->cont != NULL &&
		el->eof == 1 && det_nl(el->cont) == -1)) && ad_inf(el) == -1)
		return (-1);
	if (el->cont == NULL && el->eof == 0)
		return (0);
	nl = det_nl(el->cont);
	if (det_nl(el->cont) == -1 && el->cont != NULL && el->eof == 0)
	{
		(*line) = ft_strsub(el->cont, 0, ft_strlen(el->cont));
		ft_memdel((void **)&(el->cont));
		return (*line[0] == '\0' ? 0 : 1);
	}
	else if (nl != -1)
	{
		(*line) = ft_strsub(el->cont, 0, (size_t)nl);
		temp = ft_strdup(el->cont + nl + 1);
		ft_memdel((void **)&(el->cont));
		el->cont = ft_strdup(temp);
		ft_memdel((void **)&(temp));
		return (1);
	}
	return (check_cont(el, line));
}

static int	ad_elem(t_lst *head, int fd, char **line)
{
	t_lst *el;

	if ((el = (t_lst*)malloc(sizeof(t_lst))) == NULL)
		return (-1);
	head->next = el;
	el->fd = fd;
	el->next = NULL;
	el->eof = 1;
	el->cont = NULL;
	return (check_cont(el, line));
}

int			get_next_line(const int fd, char **line)
{
	static t_lst	*head;
	t_lst			*temp;

	if (head == NULL)
	{
		if ((head = (t_lst*)malloc(sizeof(t_lst))) == NULL)
			return (-1);
		head->fd = fd;
		head->next = NULL;
		head->eof = 1;
		head->cont = NULL;
	}
	if (head->fd == fd)
		return (check_cont(head, line));
	temp = head;
	while (temp->next)
	{
		temp = temp->next;
		if (temp->fd == fd)
			return (check_cont(temp, line));
	}
	return (ad_elem(temp, fd, line));
}
