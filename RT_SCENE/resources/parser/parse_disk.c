/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 17:44:41 by ozhovnuv          #+#    #+#             */
/*   Updated: 2017/08/21 17:44:43 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rt.h"

void	capsule_make(t_lcylinder *c, t_sphere *s1, t_sphere *s2, t_obj **obj)
{
	s1->radius = c->radius;
	s1->centre = c->top;
	s2->radius = c->radius;
	s2->centre = c->bottom;
	obj_create(obj);
	obj_add(*obj, (void*)s1, SPHERE);
	(*obj)->texture = NULL;
	(*obj)->color = (*obj)->next->color;
	(*obj)->reflection = (*obj)->next->reflection;
	(*obj)->refrection = (*obj)->next->refrection;
	(*obj)->transparency = (*obj)->next->transparency;
	obj_create(obj);
	obj_add(*obj, (void*)s2, SPHERE);
	(*obj)->texture = NULL;
	(*obj)->color = (*obj)->next->color;
	(*obj)->reflection = (*obj)->next->reflection;
	(*obj)->refrection = (*obj)->next->refrection;
	(*obj)->transparency = (*obj)->next->transparency;
}

void	parse_d(t_disk *d, char *line, t_obj **obj, t_session *ses)
{
	char *param;
	char *str;

	param = first_word(line);
	str = ft_trim(line);
	if (!ft_strcmp(param, "position:"))
		d->pos = parse_vector(str);
	else if (!ft_strcmp(param, "normal:"))
		d->normal = parse_vector(str);
	else if (!ft_strcmp(param, "radius:"))
		d->radius = parse_number(str);
	else if (!ft_strcmp(param, "innerRadius:"))
		d->in_radius = parse_number(str);
	else
		parse_param(param, str, obj, ses);
	free2(str, param);
}

void	parse_disk(t_block *head, t_obj **obj, t_session *session)
{
	t_disk	*d;
	t_block	*current;

	current = head;
	obj_create(obj);
	d = (t_disk*)malloc(sizeof(t_disk));
	*d = DEF_DISK;
	while (current != NULL)
	{
		parse_d(d, current->line, obj, session);
		current = current->next;
	}
	free_block(head);
	obj_add(*obj, (void*)d, DISK);
}

void	parse_capsule(t_block *head, t_obj **obj, t_session *session)
{
	t_lcylinder	*c;
	t_sphere	*s1;
	t_sphere	*s2;
	t_block		*current;
	t_vector	scaled;

	current = head;
	obj_create(obj);
	c = (t_lcylinder *)malloc(sizeof(t_lcylinder));
	s1 = (t_sphere *)malloc(sizeof(t_sphere));
	s2 = (t_sphere *)malloc(sizeof(t_sphere));
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
	(*obj)->texture = NULL;
	capsule_make(c, s1, s2, obj);
}
