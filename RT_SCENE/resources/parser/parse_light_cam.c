/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light_cam.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 16:31:52 by ozhovnuv          #+#    #+#             */
/*   Updated: 2017/08/21 16:32:01 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rt.h"

void	parse_cam(t_block *head, t_main *main)
{
	t_block	*current;
	char	*param;

	main->cam_rotation = v_new_data(0, 0, 0);
	current = head;
	while (current != NULL)
	{
		param = first_word(current->line);
		if (!ft_strcmp(param, "position:"))
			main->cam.start = parse_vector(current->line);
		else if (!ft_strcmp(param, "rotation:"))
			main->cam_rotation = parse_vector(current->line);
		else
			parse_error(ERROR_NOT_VALID_CAM);
		free(param);
		current = current->next;
	}
	free_block(head);
}

void	light_create(t_light **light, int type)
{
	t_light *new_light;

	new_light = (t_light*)malloc(sizeof(t_light));
	new_light->type = type;
	new_light->dir = v_new_data(0, 1, 0);
	new_light->pos = v_new_data(0, 0, 0);
	new_light->angle = 15;
	new_light->next = (*light);
	(*light) = new_light;
}

int		light_type(char *type)
{
	if (!ft_strcmp(type, "point_light"))
		return (POINT_LIGHT);
	else if (!ft_strcmp(type, "directional_light"))
		return (DIRECTIONAL_LIGHT);
	else if (!ft_strcmp(type, "parallel_light"))
		return (PARALLEL_LIGHT);
	else
		parse_error(ERROR_LIGHT_TYPE);
	return (0);
}

void	parse_light(t_block *head, t_light **obj, char *type)
{
	t_block			*current;
	char			*param;
	char			*str;

	current = head;
	light_create(obj, light_type(type));
	while (current != NULL)
	{
		param = first_word(current->line);
		str = ft_trim(current->line);
		if (!ft_strcmp(param, "position:"))
			(*obj)->pos = parse_vector(str);
		else if (!ft_strcmp(param, "direction:"))
			(*obj)->dir = parse_vector(str);
		else if (!ft_strcmp(param, "angle:"))
			(*obj)->angle = DEGREE(parse_number(str)) / 2;
		else if (!ft_strcmp(param, "intensity:"))
			(*obj)->intensity = parse_number(str);
		else
			parse_error(ERROR_NOT_VALID_PARAM);
		free2(param, str);
		current = current->next;
	}
	free_block(head);
}

void	free_str_array(char **str, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		free(str[i]);
		i++;
	}
	free(str);
}
