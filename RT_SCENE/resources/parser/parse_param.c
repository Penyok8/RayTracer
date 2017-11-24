/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 17:47:32 by ozhovnuv          #+#    #+#             */
/*   Updated: 2017/08/21 17:47:35 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rt.h"

void		parse_param(char *param, char *str, t_obj **obj, t_session *session)
{
	if (!ft_strcmp(param, "transparency:"))
		(*obj)->transparency = parse_number(str);
	else if (!ft_strcmp(param, "reflection:"))
		(*obj)->reflection = parse_number(str);
	else if (!ft_strcmp(param, "refraction:"))
		(*obj)->refrection = parse_number(str);
	else if (!ft_strcmp(param, "color:"))
		(*obj)->color = parse_color(str);
	else if (!ft_strcmp(param, "texture:"))
		obj_texture_add(str, *obj, session);
	else if (!ft_strcmp(param, "glossy:"))
		(*obj)->glosy = parse_glosy(str);
	else
		parse_error(ERROR_NOT_VALID_PARAM);
}

int			parse_glosy(char *str)
{
	char **ar;

	ar = ft_strsplit(str, ' ');
	if (arraylen(ar) != 2)
		parse_error(ERROR_GLOSY);
	if (!ft_strcmp(ar[1], "True") || !ft_strcmp(ar[1], "true"))
		return (1);
	else if (!ft_strcmp(ar[1], "False") || !ft_strcmp(ar[1], "false"))
		return (0);
	else
		parse_error(ERROR_GLOSY);
	return (0);
}

double		parse_number(char *str)
{
	char	**num;
	double	number;

	num = ft_strsplit(str, ' ');
	if (num == NULL)
		parse_error(ERROR_NUM_NOT_CORRECT);
	if (arraylen(num) == 2)
	{
		number = atod(num[1]);
		free_str_array(num, 2);
		return (number);
	}
	parse_error(ERROR_NUMBER_NOT_EXIST);
	return (0);
}

t_vector	parse_vector(char *str)
{
	char		**vec;
	int			i;
	t_vector	vector;

	vec = ft_strsplit(str, ' ');
	vector = v_new_data(0, 0, 0);
	if (vec == NULL)
		parse_error(ERROR_NOT_VALID_VECTOR);
	i = 0;
	if (arraylen(vec) == 4)
	{
		vector.x = atod(vec[1]);
		vector.y = atod(vec[2]);
		vector.z = atod(vec[3]);
		free_str_array(vec, 4);
		return (vector);
	}
	parse_error(ERROR_NOT_VALID_VECTOR);
	return (vector);
}

t_color		parse_color(char *str)
{
	char	**col;
	t_color	color;

	color = rgba(0, 0, 0, 0);
	col = ft_strsplit(str, ' ');
	if (col == NULL)
		parse_error(ERROR_NOT_VALID_COLOR);
	if (arraylen(col) == 5 || arraylen(col) == 4)
	{
		color.r = ft_atoi(col[1]);
		color.g = ft_atoi(col[2]);
		color.b = ft_atoi(col[3]);
		if (arraylen(col) == 5)
		{
			color.a = ft_atoi(col[4]);
			free_str_array(col, 5);
		}
		else
			free_str_array(col, 4);
		return (color);
	}
	parse_error(ERROR_NOT_VALID_COLOR);
	return (color);
}
