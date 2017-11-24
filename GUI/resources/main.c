/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 13:38:32 by ozhovnuv          #+#    #+#             */
/*   Updated: 2017/08/22 13:38:34 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_gui.h"

void	put_pixel(int x, int y, t_color color, t_session *ses)
{
	ses->data[y * ses->sizeline + x * 4] = color.r;
	ses->data[y * ses->sizeline + x * 4 + 1] = color.g;
	ses->data[y * ses->sizeline + x * 4 + 2] = color.b;
}

int		on_icon(int x, int y, int start_x, int start_y)
{
	if (y >= start_y && y <= start_y + ICON_HEIGHT &&
		x >= start_x && x <= start_x + ICON_WIDTH)
		return (1);
	return (0);
}

void	put_icon(int x_pos, int y_pos, t_texture *icon, t_session *ses)
{
	int icon_x;
	int icon_y;
	int x;

	icon_y = 0;
	while (y_pos < GUI_HEIGHT && icon_y < icon->height)
	{
		x = x_pos;
		icon_x = 0;
		while (x < GUI_WIDTH && icon_x < icon->width)
		{
			put_pixel(x, y_pos, icon->rgb[icon_y][icon_x], ses);
			x++;
			icon_x++;
		}
		y_pos++;
		icon_y++;
	}
	free_texture(icon);
}

void	put_main_icon(t_session *ses)
{
	put_icon(10, 10, take_xpm(ses, "./GUI/icons/logo.xpm"), ses);
	put_icon(10, 100, take_xpm(ses, "./GUI/icons/refl_icon.xpm"), ses);
	put_icon(160, 100, take_xpm(ses, "./GUI/icons/base1.xpm"), ses);
	put_icon(10, 200, take_xpm(ses, "./GUI/icons/direct.xpm"), ses);
	put_icon(160, 200, take_xpm(ses, "./GUI/icons/ellip.xpm"), ses);
	put_icon(10, 300, take_xpm(ses, "./GUI/icons/garbage.xpm"), ses);
	put_icon(160, 300, take_xpm(ses, "./GUI/icons/hole.xpm"), ses);
	put_icon(10, 400, take_xpm(ses, "./GUI/icons/parall.xpm"), ses);
	put_icon(160, 400, take_xpm(ses, "./GUI/icons/star.xpm"), ses);
	put_icon(10, 500, take_xpm(ses, "./GUI/icons/trans.xpm"), ses);
	put_icon(160, 500, take_xpm(ses, "./GUI/icons/triang.xpm"), ses);
	put_icon(10, 600, take_xpm(ses, "./GUI/icons/el_tra.xpm"), ses);
	put_icon(160, 600, take_xpm(ses, "./GUI/icons/art.xpm"), ses);
	put_icon(10, 700, take_xpm(ses, "./GUI/icons/capsule.xpm"), ses);
	put_icon(160, 700, take_xpm(ses, "./GUI/icons/new.xpm"), ses);
	put_icon(10, 800, take_xpm(ses, "./GUI/icons/doc_icon.xpm"), ses);
	put_icon(160, 800, take_xpm(ses, "./GUI/icons/team_icon.xpm"), ses);
	put_icon(85, 900, take_xpm(ses, "./GUI/icons/video_icon.xpm"), ses);
}

int		main(void)
{
	t_session	*ses;

	ses = (t_session*)malloc(sizeof(t_session));
	ses->mlx = mlx_init();
	ses->win = mlx_new_window(ses->mlx, GUI_WIDTH, GUI_HEIGHT, "RT");
	ses->bpp = 32;
	ses->endian = 0;
	ses->ini = mlx_new_image(ses->mlx, GUI_WIDTH, GUI_HEIGHT);
	ses->data = mlx_get_data_addr(ses->ini, &(ses->bpp),
	&(ses->sizeline), &(ses->endian));
	put_main_icon(ses);
	ses->gui_start = ft_strdup(ses->data);
	mlx_put_image_to_window(ses->mlx, ses->win, ses->ini, 0, 0);
	ses->icon = 0;
	mlx_hook(ses->win, 2, 5, key_action, 0);
	mlx_hook(ses->win, 17, 0, close_window, NULL);
	mlx_mouse_hook(ses->win, mouse_action, ses);
	mlx_loop(ses->mlx);
}
