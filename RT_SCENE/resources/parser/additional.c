/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <ozhovnuv@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/03 14:41:01 by ozhovnuv          #+#    #+#             */
/*   Updated: 2017/08/20 18:40:20 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rt.h"

void		intersection_type(t_obj *obj, int type)
{
	if (type == SPHERE)
		obj->intersection = intersect_sphere;
	else if (type == CONE)
		obj->intersection = intersect_cone;
	else if (type == PLANE)
		obj->intersection = intersect_plane;
	else if (type == CYLINDER)
		obj->intersection = intersect_cylinder;
	else if (type == DISK)
		obj->intersection = intersect_disk;
	else if (type == LIMITED_CYLINDER)
		obj->intersection = intersect_lcylinder;
	else if (type == TRIANGLE)
		obj->intersection = intersect_triangle;
	else if (type == TUBE)
		obj->intersection = intersect_tube;
	else if (type == ELLIPSE)
		obj->intersection = intersect_ellipse;
}

void		normal_type(t_obj *obj, int type)
{
	if (type == SPHERE)
		obj->find_normal = normal_sphere;
	else if (type == CONE)
		obj->find_normal = normal_cone;
	else if (type == PLANE)
		obj->find_normal = normal_plane;
	else if (type == CYLINDER)
		obj->find_normal = normal_cylinder;
	else if (type == DISK)
		obj->find_normal = normal_disk;
	else if (type == LIMITED_CYLINDER)
		obj->find_normal = normal_lcylinder;
	else if (type == TRIANGLE)
		obj->find_normal = normal_triangle;
	else if (type == TUBE)
		obj->find_normal = normal_tube;
	else if (type == ELLIPSE)
		obj->find_normal = normal_ellipse;
}

void		texture_type(t_obj *obj, int type)
{
	if (type == SPHERE)
		obj->texture_obj = texture_sphere;
	else if (type == PLANE)
		obj->texture_obj = texture_plane;
	else if (type == LIMITED_CYLINDER)
		obj->texture_obj = texture_cylinder;
	else if (type == DISK)
		obj->texture_obj = texture_plane;
	else if (type == ELLIPSE)
		obj->texture_obj = texture_sphere;
}

void		obj_create(t_obj **head)
{
	t_obj *new_obj;

	new_obj = (t_obj*)malloc(sizeof(t_obj));
	new_obj->obj = NULL;
	new_obj->transparency = 0;
	new_obj->reflection = 0;
	new_obj->refrection = 0;
	new_obj->glosy = 0;
	new_obj->color = rgba(0, 0, 0, 0);
	new_obj->texture = NULL;
	new_obj->next = (*head);
	(*head) = new_obj;
}

void		obj_add(t_obj *head, void *obj, int type)
{
	double sum;

	head->obj = obj;
	sum = head->transparency + head->reflection;
	if (sum > 1.0)
	{
		sum += 0.001;
		head->transparency /= sum;
		head->reflection /= sum;
	}
	intersection_type(head, type);
	normal_type(head, type);
	texture_type(head, type);
}
