/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 17:37:23 by ozhovnuv          #+#    #+#             */
/*   Updated: 2017/08/21 17:37:25 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rt.h"

void	parse_sphere(t_block *head, t_obj **obj, t_session *session)
{
	t_sphere	*s;
	t_block		*current;
	char		*param;
	char		*str;

	current = head;
	obj_create(obj);
	s = (t_sphere*)malloc(sizeof(t_sphere));
	*s = DEF_SPHERE;
	while (current != NULL)
	{
		param = first_word(current->line);
		str = ft_trim(current->line);
		if (!ft_strcmp(param, "position:"))
			s->centre = parse_vector(str);
		else if (!ft_strcmp(param, "radius:"))
			s->radius = parse_number(str);
		else
			parse_param(param, str, obj, session);
		free2(str, param);
		current = current->next;
	}
	free_block(head);
	obj_add(*obj, (void*)s, SPHERE);
}

void	parse_cyl(t_cylinder *c, char *line, t_obj **obj, t_session *ses)
{
	char *param;
	char *str;

	param = first_word(line);
	str = ft_trim(line);
	if (!ft_strcmp(param, "position:"))
		c->pos = parse_vector(str);
	else if (!ft_strcmp(param, "direction:"))
		c->rot = parse_vector(str);
	else if (!ft_strcmp(param, "radius:"))
		c->radius = parse_number(str);
	else
		parse_param(param, str, obj, ses);
	free2(str, param);
}

void	parse_cylinder(t_block *head, t_obj **obj, t_session *session)
{
	t_cylinder	*c;
	t_block		*current;

	current = head;
	obj_create(obj);
	c = (t_cylinder*)malloc(sizeof(t_cylinder));
	*c = DEF_CYL;
	while (current != NULL)
	{
		parse_cyl(c, current->line, obj, session);
		current = current->next;
	}
	free_block(head);
	obj_add(*obj, (void*)c, CYLINDER);
}

void	parse_lcyl(t_lcylinder *c, char *line, t_obj **obj, t_session *ses)
{
	char *param;
	char *str;

	param = first_word(line);
	str = ft_trim(line);
	if (!ft_strcmp(param, "position:"))
		c->centre = parse_vector(str);
	else if (!ft_strcmp(param, "rotation:"))
		c->rot = parse_vector(str);
	else if (!ft_strcmp(param, "radius:"))
		c->radius = parse_number(str);
	else if (!ft_strcmp(param, "length:"))
		c->length = parse_number(str);
	else
		parse_param(param, str, obj, ses);
	free2(str, param);
}

void	parse_lcylinder(t_block *head, t_obj **obj, t_session *session)
{
	t_lcylinder	*c;
	t_block		*current;
	t_vector	scaled;

	current = head;
	obj_create(obj);
	c = (t_lcylinder*)malloc(sizeof(t_lcylinder));
	*c = DEF_LCYL;
	while (current != NULL)
	{
		parse_lcyl(c, current->line, obj, session);
		current = current->next;
	}
	scaled = vector_scale(&c->rot, (double)c->length / 2);
	c->top = vector_add(&c->centre, &scaled);
	c->bottom = vector_sub(&c->centre, &scaled);
	free_block(head);
	obj_add(*obj, (void*)c, LIMITED_CYLINDER);
}
