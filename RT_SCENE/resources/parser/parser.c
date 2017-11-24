/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 16:38:12 by ozhovnuv          #+#    #+#             */
/*   Updated: 2017/08/21 16:38:14 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rt.h"

int		parse_error_plus(int error)
{
	if (error == ERROR_PARSE_BLOCK)
		printf("Parse error: NOT VALID BLOCK NAME\n");
	else if (error == ERROR_NUM_NOT_CORRECT)
		printf("Parse error: NOT VALID NUMBER\n");
	else if (error == ERROR_NOT_VALID_COLOR)
		printf("Parse error: NOT VALID COLOR\n");
	else if (error == ERROR_NOT_VALID_VECTOR)
		printf("Parse error: NOT VALID VECTOR\n");
	else if (error == ERROR_NUMBER_NOT_EXIST)
		printf("Parse error: NUMBER NOT EXIST\n");
	else if (error == ERROR_BLOCK_NOT_EXIST)
		printf("Parse error: BLOCK NAME NOT EXIST\n");
	else if (error == ERROR_NOT_VALID_CAM)
		printf("Parse error: NOT VALID CAM PARAM\n");
	else if (error == ERROR_NOT_VALID_PARAM)
		printf("Parse error: NOT VALID PARAM\n");
	else
		return (0);
	return (1);
}

void	parse_error(int error)
{
	if (parse_error_plus(error))
	{
		exit(0);
	}
	else if (error == ERROR_TEXTURE_FILE)
		printf("Parse error: NOT VALID TEXTURE FILE\n");
	else if (error == ERROR_LIGHT_TYPE)
		printf("Parse error: NOT CORRECT LIGHT TYPE\n");
	else if (error == ERROR_EMPTY_LINE)
		printf("Parse error: EMPTY LINE\n");
	else if (error == ERROR_GLOSY)
		printf("Parse error: NOT VALID GLOSY\n");
	else if (error == ERROR_NOT_CORRECT_FILE)
		printf("NOT CORRECT FILE OR PATH\n");
	else if (error == ERROR_FILTER_NOT_EXIST)
		printf("Parse error: FILTER NOT EXIST\n");
	else
		printf("PARSE ERROR\n");
	exit(0);
}

int		parser_obj_equation(char *str, int fd, t_session *session, t_obj **obj)
{
	if (!ft_strcmp(str, "sphere"))
		parse_sphere(get_block(fd), obj, session);
	else if (!ft_strcmp(str, "disk"))
		parse_disk(get_block(fd), obj, session);
	else if (!ft_strcmp(str, "plane"))
		parse_plane(get_block(fd), obj, session);
	else if (!ft_strcmp(str, "cylinder"))
		parse_cylinder(get_block(fd), obj, session);
	else if (!ft_strcmp(str, "cone"))
		parse_cone(get_block(fd), obj, session);
	else if (!ft_strcmp(str, "limited_cylinder"))
		parse_lcylinder(get_block(fd), obj, session);
	else if (!ft_strcmp(str, "tube"))
		parse_tube(get_block(fd), obj, session);
	else if (!ft_strcmp(str, "triangle"))
		parse_triangle(get_block(fd), obj, session);
	else if (!ft_strcmp(str, "ellipse"))
		parse_ellipse(get_block(fd), obj, session);
	else if (!ft_strcmp(str, "capsule"))
		parse_capsule(get_block(fd), obj, session);
	else
		return (0);
	return (1);
}

int		parser_addition(char *str, int fd, t_light **light, t_main *main)
{
	if (!ft_strcmp(str, "cam"))
		parse_cam(get_block(fd), main);
	else if (ft_strstr(str, "light") != NULL)
		parse_light(get_block(fd), light, str);
	else if (!ft_strcmp(str, "soft_shadows"))
		parse_soft_shadows(get_block(fd), main);
	else if (!ft_strcmp(str, "threads"))
		parse_soft_shadows(get_block(fd), main);
	else if (!ft_strcmp(str, "visual_effects"))
		parse_filter(get_block(fd), main);
	else
		return (0);
	return (1);
}

void	parser(int fd, t_main *main, t_session *session)
{
	char	*line;
	char	*str;
	t_obj	*obj;
	t_light *light;

	obj = NULL;
	light = NULL;
	while (get_next_line(fd, &line))
	{
		str = ft_trim(line);
		if (parser_obj_equation(str, fd, session, &obj))
			free2(str, line);
		else if (parser_addition(str, fd, &light, main))
			free2(str, line);
		else
			parse_error(ERROR_BLOCK_NOT_EXIST);
	}
	light_equalize(light);
	main->obj = obj;
	main->light = light;
}
