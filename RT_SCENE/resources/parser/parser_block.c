/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_block.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 16:35:18 by ozhovnuv          #+#    #+#             */
/*   Updated: 2017/08/21 16:35:20 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rt.h"

void	free_block(t_block *head)
{
	t_block *tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp->line);
		free(tmp);
	}
}

void	push_block(t_block *head, char *line)
{
	t_block *tmp;
	t_block	*current;

	current = head;
	if (current->line == NULL)
	{
		current->line = ft_strdup(line);
		current->next = NULL;
	}
	else
	{
		while (current->next != NULL)
		{
			current = current->next;
		}
		tmp = (t_block*)malloc(sizeof(t_block));
		tmp->line = ft_strdup(line);
		tmp->next = NULL;
		current->next = tmp;
	}
}

t_block	*get_block(int fd)
{
	char	*line;
	t_block	*block;
	char	*str;

	block = (t_block*)malloc(sizeof(t_block));
	block->line = NULL;
	if (!get_next_line(fd, &line) || ft_strcmp((str = ft_trim(line)), "{") != 0)
		parse_error(ERROR_PARSE_BLOCK);
	free2(str, line);
	while (get_next_line(fd, &line) && line[0] != '\0')
	{
		str = ft_trim(line);
		if (ft_strcmp(str, "}") == 0)
		{
			free2(str, line);
			return (block);
		}
		push_block(block, str);
		free2(str, line);
	}
	parse_error(ERROR_PARSE_BLOCK);
	return (NULL);
}

t_color	rgba(int r, int g, int b, int alpha)
{
	t_color color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = alpha;
	return (color);
}

void	light_equalize(t_light *head)
{
	t_light	*current;
	double	light_sum;

	light_sum = 0;
	current = head;
	while (current != NULL)
	{
		light_sum += current->intensity;
		current = current->next;
	}
	if (light_sum > 1)
	{
		current = head;
		while (current != NULL)
		{
			current->intensity /= light_sum;
			current = current->next;
		}
	}
}
