/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <ozhovnuv@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 16:49:35 by ozhovnuv          #+#    #+#             */
/*   Updated: 2017/07/10 19:40:48 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rt.h"

void		fill_color(t_thread *flow, int x, int y, t_color color)
{
	flow->session->data[y * flow->session->sizeline + x * 4] = color.r;
	flow->session->data[y * flow->session->sizeline + x * 4 + 1] = color.g;
	flow->session->data[y * flow->session->sizeline + x * 4 + 2] = color.b;
	flow->session->data[y * flow->session->sizeline + x * 4 + 3] = color.a;
}

t_color		anti_alias(t_thread *flow, int x, int y)
{
	double	x_x;
	double	y_y;
	t_color	n_col;
	t_color	color;

	x_x = x;
	y_y = y;
	color = BLACK;
	while (x_x < x + 1)
	{
		y_y = y;
		while (y_y < y + 1)
		{
			flow->main.cam.dir = ray_dir_init(&flow->main, x_x, y_y);
			n_col = cast_ray(flow->main.cam, 1, &flow->main);
			n_col = color_scale(n_col, 0.25);
			color = color_add(color, n_col);
			y_y += 0.5;
		}
		x_x += 0.5;
	}
	return (color);
}

void		*trace(void *thread_elem)
{
	t_thread	*flow;
	int			y;
	int			x;
	t_color		color;

	flow = (t_thread*)thread_elem;
	y = flow->thread_num;
	color = BLACK;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			color = anti_alias(flow, x, y);
			fill_color(flow, x, y, color);
			color = BLACK;
			x++;
		}
		y += flow->main.threads_num - 1;
	}
	return (NULL);
}
