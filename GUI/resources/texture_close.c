/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_close.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:09:45 by ozhovnuv          #+#    #+#             */
/*   Updated: 2017/08/23 13:09:47 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_gui.h"

int			close_window(void)
{
	exit(0);
	return (0);
}

int			key_action(int button, int zero)
{
	if (button == 53)
		exit(zero);
	return (0);
}

t_texture	*take_xpm(t_session *session, char *file)
{
	t_texture	*text;
	int			i;
	int			j;

	text = (t_texture*)malloc(sizeof(t_texture));
	text->xpm = mlx_xpm_file_to_image(session->mlx,
		file, &(text->width), &(text->height));
	if (!text->xpm)
		exit(0);
	text->data = mlx_get_data_addr(text->xpm, &(session->bpp),
	&(text->sizeline), &(session->endian));
	text->rgb = (t_color**)malloc(sizeof(t_color*) * text->height);
	i = -1;
	while (++i < text->height)
	{
		text->rgb[i] = (t_color*)malloc(sizeof(t_color) * text->width);
		j = -1;
		while (++j < text->width)
		{
			text->rgb[i][j].r = text->data[i * text->sizeline + j * 4];
			text->rgb[i][j].g = text->data[i * text->sizeline + j * 4 + 1];
			text->rgb[i][j].b = text->data[i * text->sizeline + j * 4 + 2];
		}
	}
	return (text);
}

void		free_texture(t_texture *text)
{
	int y;

	y = 0;
	while (y < text->height)
	{
		free(text->rgb[y]);
		text->rgb[y] = NULL;
		y++;
	}
	free(text->rgb);
	free(text);
}
