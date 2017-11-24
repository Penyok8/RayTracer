/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_gui.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:14:11 by ozhovnuv          #+#    #+#             */
/*   Updated: 2017/08/23 13:14:14 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_GUI_H
# define RT_GUI_H
# include "../../minilibx_macos/mlx.h"
# include "../../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

# define GUI_WIDTH 300
# define GUI_HEIGHT 1000
# define ICON_WIDTH 130
# define ICON_HEIGHT 80

# define RED (t_color){0, 0, 255, 0}
# define GREEN (t_color){0, 255, 0, 0}
# define BACKGROUND (t_color){53, 171, 255}

typedef struct	s_color
{
	double		r;
	double		g;
	double		b;
	double		a;
}				t_color;

typedef struct	s_texture
{
	void		*xpm;
	char		*data;
	int			sizeline;
	int			width;
	int			height;
	t_color		**rgb;
}				t_texture;

typedef struct	s_session
{
	void		*ini;
	char		*data;
	void		*mlx;
	void		*win;
	int			bpp;
	int			sizeline;
	int			endian;
	int			icon;
	char		*gui_start;
}				t_session;

int				mouse_action(int button, int x, int y, t_session *ses);
void			free_texture(t_texture *text);
int				close_window(void);
int				key_action(int button, int zero);
t_texture		*take_xpm(t_session *session, char *file);
void			put_pixel(int x, int y, t_color color, t_session *ses);
int				on_icon(int x, int y, int start_x, int start_y);
void			put_icon(int x_pos, int y_pos, t_texture *icon, t_session *ses);
void			put_main_icon(t_session *ses);
#endif
