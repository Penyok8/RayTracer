/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <ozhovnuv@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 16:49:35 by ozhovnuv          #+#    #+#             */
/*   Updated: 2017/07/10 19:40:48 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rt.h"

t_texture		*take_xpm(t_session *ses, char *file)
{
	t_texture	*text;
	int			i;
	int			j;

	text = (t_texture*)malloc(sizeof(t_texture));
	text->xpm = mlx_xpm_file_to_image(ses->mlx, file, &(text->w), &(text->h));
	if (!text->xpm)
		parse_error(ERROR_TEXTURE_FILE);
	text->data = mlx_get_data_addr(text->xpm, &(ses->bpp),
	&(text->sizeline), &(ses->endian));
	text->rgb = (t_color**)malloc(sizeof(t_color*) * text->h);
	i = -1;
	while (++i < text->h)
	{
		text->rgb[i] = (t_color*)malloc(sizeof(t_color) * text->w);
		j = -1;
		while (++j < text->w)
		{
			text->rgb[i][j].r = text->data[i * text->sizeline + j * 4];
			text->rgb[i][j].g = text->data[i * text->sizeline + j * 4 + 1];
			text->rgb[i][j].b = text->data[i * text->sizeline + j * 4 + 2];
			text->rgb[i][j].a = text->data[i * text->sizeline + j * 4 + 3];
		}
	}
	return (text);
}

void			texture_plane(void *id, t_obj *obj, t_vector hit_point)
{
	t_plane		*plane;
	t_texture	text;

	plane = (t_plane *)(id);
	text.v_p = vector_sub(&hit_point, &plane->pos);
	if (plane->normal.x > 0)
		text.v_x = v_new_data(0, 0.5, 0.5);
	if (plane->normal.y > 0)
		text.v_x = v_new_data(0.5, 0, 0.5);
	else
		text.v_x = v_new_data(-0.5, 0, 0.5);
	text.v_y = v_cross(text.v_x, plane->normal);
	text.v = round(fabs(vector_dot(&text.v_p, &text.v_y)));
	text.u = round(fabs(vector_dot(&text.v_p, &text.v_x)));
	text.v = (abs((int)round((int)text.v % obj->texture->h - 1)));
	text.u = (abs((int)round((int)text.u % obj->texture->w - 1)));
	if (find_cos_vectors(&text.v_p, &text.v_x) > 0)
		text.u = round((obj->texture->w - 1) - text.u);
	if (find_cos_vectors(&text.v_p, &text.v_y) > 0)
		text.v = round((obj->texture->h - 1) - text.v);
	obj->color.r = obj->texture->rgb[(int)text.v][(int)text.u].r;
	obj->color.g = obj->texture->rgb[(int)text.v][(int)text.u].g;
	obj->color.b = obj->texture->rgb[(int)text.v][(int)text.u].b;
	obj->color.a = obj->texture->rgb[(int)text.v][(int)text.u].a;
}

void			texture_sphere(void *id, t_obj *obj, t_vector hit_point)
{
	t_sphere	*sphere;
	t_texture	text;

	sphere = (t_sphere *)(id);
	text.v_y = v_new_data(0, 1, 0);
	text.v_x = v_new_data(1, 0, 0);
	text.v_p = vector_sub(&sphere->centre, &hit_point);
	text.v_p = normalize(&text.v_p);
	text.phi = acos(-vector_dot(&text.v_p, &text.v_y));
	text.v = text.phi / M_PI;
	text.theta = (acos(vector_dot(&text.v_p, &text.v_x) /
		sin(text.phi))) / (2 * M_PI);
	text.tmp = v_cross(text.v_x, text.v_y);
	if (vector_dot(&text.tmp, &text.v_p) > 0)
		text.u = text.theta;
	else
		text.u = 1 - text.theta;
	text.v = round(text.v * obj->texture->h - 1);
	text.u = round(text.u * obj->texture->w - 1);
	obj->color.r = obj->texture->rgb[(int)text.v][(int)text.u].r;
	obj->color.g = obj->texture->rgb[(int)text.v][(int)text.u].g;
	obj->color.b = obj->texture->rgb[(int)text.v][(int)text.u].b;
	obj->color.a = obj->texture->rgb[(int)text.v][(int)text.u].a;
}

void			texture_cylinder(void *id, t_obj *obj, t_vector hit_point)
{
	t_lcylinder	*lcylinder;
	t_texture	text;

	lcylinder = (t_lcylinder *)(id);
	if (lcylinder->rot.x > 0)
		text.v_x = v_new_data(0, 1, 0);
	if (lcylinder->rot.y > 0)
		text.v_x = v_new_data(1, 0, 0);
	text.v_x = v_cross(v_cross(text.v_x, lcylinder->rot), lcylinder->rot);
	text.v_p = vector_sub(&hit_point, &lcylinder->top);
	text.v = v_magnitude(vector_scale(&lcylinder->rot,
		vector_dot(&text.v_p, &lcylinder->rot)));
	text.v_p = normalize(&text.v_p);
	text.phi = acos(-vector_dot(&text.v_p, &lcylinder->rot));
	text.theta = (acos(vector_dot(&text.v_p, &text.v_x) /
		sin(text.phi))) / (2 * M_PI);
	text.tmp = v_cross(text.v_x, lcylinder->rot);
	text.u = vector_dot(&text.tmp, &text.v_p) > 0 ? text.theta : 1 - text.theta;
	text.v = (int)text.v % obj->texture->h;
	text.u = round(text.u * obj->texture->w);
	obj->color.r = obj->texture->rgb[(int)text.v][(int)text.u].r;
	obj->color.g = obj->texture->rgb[(int)text.v][(int)text.u].g;
	obj->color.b = obj->texture->rgb[(int)text.v][(int)text.u].b;
	obj->color.a = obj->texture->rgb[(int)text.v][(int)text.u].a;
}
