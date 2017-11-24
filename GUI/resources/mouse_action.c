/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:09:36 by ozhovnuv          #+#    #+#             */
/*   Updated: 2017/08/23 13:09:38 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_gui.h"

void	left_mouseb_add(int x, int y, t_session *ses)
{
	if (on_icon(x, y, 160, 600))
		system("cd RT_SCENE && ./RT_SCENE ./scenes/art");
	else if (on_icon(x, y, 10, 700))
		system("cd RT_SCENE && ./RT_SCENE ./scenes/capsule");
	else if (on_icon(x, y, 160, 700))
		system("cd RT_SCENE && ./RT_SCENE ./scenes/new_scene");
	else if (on_icon(x, y, 10, 800))
		system("open RT_SCENE/documentation.txt");
	else if (on_icon(x, y, 160, 800))
		system("open author");
	else if (on_icon(x, y, 85, 900))
		system("open https://forum.intra.42.fr/topics/17456/messages?page=1#77145");
}

void	left_mouseb(int x, int y, t_session *ses)
{
	if (on_icon(x, y, 10, 100))
		system("cd RT_SCENE && ./RT_SCENE ./scenes/reflection");
	else if (on_icon(x, y, 160, 100))
		system("cd RT_SCENE && ./RT_SCENE ./scenes/basic1");
	else if (on_icon(x, y, 10, 200))
		system("cd RT_SCENE && ./RT_SCENE ./scenes/directional_light");
	else if (on_icon(x, y, 160, 200))
		system("cd RT_SCENE && ./RT_SCENE ./scenes/multispot");
	else if (on_icon(x, y, 10, 300))
		system("cd RT_SCENE && ./RT_SCENE ./scenes/trash");
	else if (on_icon(x, y, 160, 300))
		system("cd RT_SCENE && ./RT_SCENE ./scenes/black_hole");
	else if (on_icon(x, y, 10, 400))
		system("cd RT_SCENE && ./RT_SCENE ./scenes/parallel_light");
	else if (on_icon(x, y, 160, 400))
		system("cd RT_SCENE && ./RT_SCENE ./scenes/light_sabers");
	else if (on_icon(x, y, 10, 500))
		system("cd RT_SCENE && ./RT_SCENE ./scenes/refraction");
	else if (on_icon(x, y, 160, 500))
		system("cd RT_SCENE && ./RT_SCENE ./scenes/cristall");
	else if (on_icon(x, y, 10, 600))
		system("cd RT_SCENE && ./RT_SCENE ./scenes/ellipse");
	else
		left_mouseb_add(x, y, ses);
}

void	right_mouseb_add(int x, int y, t_session *ses)
{
	if (on_icon(x, y, 160, 500))
		system("open RT_SCENE/scenes/cristall");
	else if (on_icon(x, y, 10, 600))
		system("open RT_SCENE/scenes/ellipse");
	else if (on_icon(x, y, 160, 600))
		system("open RT_SCENE/scenes/art");
	else if (on_icon(x, y, 10, 700))
		system("open RT_SCENE/scenes/capsule");
	else if (on_icon(x, y, 160, 700))
		system("open RT_SCENE/scenes/new_scene");
	else if (on_icon(x, y, 160, 800))
		system("open ./author");
}

void	right_mouseb(int x, int y, t_session *ses)
{
	if (on_icon(x, y, 10, 100))
		system("open RT_SCENE/scenes/reflection");
	else if (on_icon(x, y, 160, 100))
		system("open RT_SCENE/scenes/basic1");
	else if (on_icon(x, y, 10, 200))
		system("open RT_SCENE/scenes/directional_light");
	else if (on_icon(x, y, 160, 200))
		system("open RT_SCENE/scenes/multispot");
	else if (on_icon(x, y, 10, 300))
		system("open RT_SCENE/scenes/trash");
	else if (on_icon(x, y, 160, 300))
		system("open RT_SCENE/scenes/black_hole");
	else if (on_icon(x, y, 10, 400))
		system("open RT_SCENE/scenes/parallel_light");
	else if (on_icon(x, y, 160, 400))
		system("open RT_SCENE/scenes/light_sabers");
	else if (on_icon(x, y, 10, 500))
		system("open RT_SCENE/scenes/refraction");
	else
		right_mouseb_add(x, y, ses);
}

int		mouse_action(int button, int x, int y, t_session *ses)
{
	if (button == 1 && x >= 0 && x <= GUI_WIDTH && y >= 0 && y <= GUI_HEIGHT)
	{
		left_mouseb(x, y, ses);
	}
	else if (button == 2 && x >= 0 && x <= GUI_WIDTH
			&& y >= 0 && y <= GUI_HEIGHT)
	{
		right_mouseb(x, y, ses);
	}
	return (0);
}
