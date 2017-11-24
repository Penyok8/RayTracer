/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_texture_shadows.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 16:39:26 by ozhovnuv          #+#    #+#             */
/*   Updated: 2017/08/21 16:39:28 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rt.h"

void	filter_choice(char *param, t_main *main)
{
	if (!ft_strcmp(param, "negative"))
		main->filter = FIL_NEG;
	else if (!ft_strcmp(param, "black_white"))
		main->filter = FIL_B_W;
	else
		parse_error(ERROR_FILTER_NOT_EXIST);
}

void	parse_filter(t_block *head, t_main *main)
{
	t_block		*current;
	char		*param;
	char		*str;
	char		**arr;

	current = head;
	while (current != NULL)
	{
		param = first_word(current->line);
		str = ft_trim(current->line);
		if (!ft_strcmp(param, "filter:"))
		{
			arr = ft_strsplit(str, ' ');
			if (arraylen(arr) != 2)
				parse_error(ERROR_NOT_VALID_PARAM);
			filter_choice(arr[1], main);
			free_str_array(arr, 2);
		}
		else
			parse_error(ERROR_NOT_VALID_PARAM);
		free2(str, param);
		current = current->next;
	}
	free_block(head);
}

void	obj_texture_add(char *str, t_obj *obj, t_session *session)
{
	char **arr;

	arr = ft_strsplit(str, ' ');
	if (arraylen(arr) != 2)
		parse_error(ERROR_TEXTURE_FILE);
	obj->texture = take_xpm(session, arr[1]);
	free_str_array(arr, 2);
}

void	parse_soft_shadows(t_block *head, t_main *main)
{
	t_block		*current;
	char		*param;
	char		*str;

	current = head;
	while (current != NULL)
	{
		param = first_word(current->line);
		str = ft_trim(current->line);
		if (!ft_strcmp(param, "rays:"))
		{
			main->ss_rays = (int)parse_number(str);
			main->ss_ray_iter = main->ss_rays > 0 ? main->ss_rays : 1;
		}
		else
			parse_error(ERROR_NOT_VALID_PARAM);
		free2(str, param);
		current = current->next;
	}
	free_block(head);
}

void	free2(char *str, char *str2)
{
	free(str);
	free(str2);
}
