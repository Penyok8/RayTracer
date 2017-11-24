/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone_triangle.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 17:44:54 by ozhovnuv          #+#    #+#             */
/*   Updated: 2017/08/21 17:44:58 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rt.h"

void	parse_ellipse(t_block *head, t_obj **obj, t_session *session)
{
	t_ellipse	*p;
	t_block		*current;
	char		*param;
	char		*str;

	current = head;
	obj_create(obj);
	p = (t_ellipse*)malloc(sizeof(t_ellipse));
	while (current != NULL)
	{
		param = first_word(current->line);
		str = ft_trim(current->line);
		if (!ft_strcmp(param, "position:"))
			p->position = parse_vector(str);
		else if (!ft_strcmp(param, "size:"))
			p->size = parse_vector(str);
		else
			parse_param(param, str, obj, session);
		free2(str, param);
		current = current->next;
	}
	free_block(head);
	obj_add(*obj, (void*)p, ELLIPSE);
}

void	parse_co(t_cone *c, char *line, t_obj **obj, t_session *ses)
{
	char	*param;
	char	*str;

	param = first_word(line);
	str = ft_trim(line);
	if (!ft_strcmp(param, "position:"))
		c->pos = parse_vector(str);
	else if (!ft_strcmp(param, "direction:"))
		c->rot = parse_vector(str);
	else if (!ft_strcmp(param, "angle:"))
		c->angle = DEGREE(parse_number(str));
	else
		parse_param(param, str, obj, ses);
	free2(str, param);
}

void	parse_cone(t_block *head, t_obj **obj, t_session *session)
{
	t_cone	*c;
	t_block	*current;

	c = (t_cone*)malloc(sizeof(t_cone));
	obj_create(obj);
	current = head;
	*c = DEF_CONE;
	while (current != NULL)
	{
		parse_co(c, current->line, obj, session);
		current = current->next;
	}
	free_block(head);
	obj_add(*obj, (void*)c, CONE);
}

void	parse_tr(t_triangle *tr, char *line, t_obj **obj, t_session *ses)
{
	char *param;
	char *str;

	param = first_word(line);
	str = ft_trim(line);
	if (!ft_strcmp(param, "point0:"))
		tr->v0 = parse_vector(str);
	else if (!ft_strcmp(param, "point1:"))
		tr->v1 = parse_vector(str);
	else if (!ft_strcmp(param, "point2:"))
		tr->v2 = parse_vector(str);
	else
		parse_param(param, str, obj, ses);
	free2(str, param);
}

void	parse_triangle(t_block *head, t_obj **obj, t_session *session)
{
	t_triangle	*tr;
	t_block		*current;

	tr = (t_triangle*)malloc(sizeof(t_triangle));
	obj_create(obj);
	current = head;
	*tr = DEF_TR;
	while (current != NULL)
	{
		parse_tr(tr, current->line, obj, session);
		current = current->next;
	}
	tr->e1 = v_diff(tr->v1, tr->v0);
	tr->e2 = v_diff(tr->v2, tr->v0);
	tr->normal = v_normalize(v_cross(tr->e1, tr->e2));
	free_block(head);
	obj_add(*obj, (void*)tr, TRIANGLE);
}
