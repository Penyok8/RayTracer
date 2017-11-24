/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_plane_tube.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 17:37:09 by ozhovnuv          #+#    #+#             */
/*   Updated: 2017/08/21 17:37:11 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rt.h"

void	parse_tub(t_tube *tube, char *line, t_obj **obj, t_session *ses)
{
	char *param;
	char *str;

	param = first_word(line);
	str = ft_trim(line);
	if (!ft_strcmp(param, "position:"))
		tube->pos = parse_vector(str);
	else if (!ft_strcmp(param, "direction:"))
		tube->rot = parse_vector(str);
	else if (!ft_strcmp(param, "length:"))
		tube->len = parse_number(str);
	else if (!ft_strcmp(param, "radius:"))
		tube->radius = parse_number(str);
	else
		parse_param(param, str, obj, ses);
	free2(str, param);
}

void	parse_tube(t_block *head, t_obj **obj, t_session *session)
{
	t_tube		*c;
	t_block		*current;
	t_vector	scaled;

	current = head;
	obj_create(obj);
	c = (t_tube*)malloc(sizeof(t_tube));
	*c = DEF_TUBE;
	while (current != NULL)
	{
		parse_tub(c, current->line, obj, session);
		current = current->next;
	}
	c->rot = normalize(&c->rot);
	scaled = vector_scale(&c->rot, (double)c->len / 2);
	c->top = vector_add(&c->pos, &scaled);
	c->bottom = vector_sub(&c->pos, &scaled);
	free_block(head);
	obj_add(*obj, (void*)c, TUBE);
}

void	parse_pl(t_plane *p, char *line, t_obj **obj, t_session *ses)
{
	char *param;
	char *str;

	param = first_word(line);
	str = ft_trim(line);
	if (!ft_strcmp(param, "position:"))
		p->pos = parse_vector(str);
	else if (!ft_strcmp(param, "normal:"))
		p->normal = parse_vector(str);
	else if (!ft_strcmp(param, "sphereRadius:"))
		p->sphere_radius = parse_number(str);
	else
		parse_param(param, str, obj, ses);
	free2(str, param);
}

void	parse_plane(t_block *head, t_obj **obj, t_session *session)
{
	t_plane	*p;
	t_block	*current;

	current = head;
	obj_create(obj);
	p = (t_plane*)malloc(sizeof(t_plane));
	*p = DEF_PL;
	while (current != NULL)
	{
		parse_pl(p, current->line, obj, session);
		current = current->next;
	}
	free_block(head);
	obj_add(*obj, (void*)p, PLANE);
}
