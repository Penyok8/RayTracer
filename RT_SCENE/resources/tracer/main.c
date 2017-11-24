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

int			key_action(int button, int zero)
{
	if (button == 53)
		exit(zero);
	return (0);
}

int			close_window(void)
{
	exit(0);
	return (0);
}

static void	create_session(t_session *session)
{
	session->mlx = mlx_init();
	session->win = mlx_new_window(session->mlx, WIDTH, HEIGHT, "RT");
	session->bpp = 32;
	session->endian = 0;
	session->ini = mlx_new_image(session->mlx, WIDTH, HEIGHT);
	session->data = mlx_get_data_addr(session->ini, &(session->bpp),
	&(session->sizeline), &(session->endian));
}

void		thread(t_main main, t_session *session)
{
	int			i;
	pthread_t	*thread;
	t_thread	*flows;

	i = -1;
	thread = (pthread_t *)malloc(sizeof(pthread_t) * (main.threads_num));
	flows = (t_thread *)malloc(sizeof(t_thread) * (main.threads_num));
	while (++i < main.threads_num)
	{
		flows[i].main = main;
		flows[i].session = session;
		flows[i].thread_num = i;
		pthread_create(&thread[i], NULL, trace, (void*)&flows[i]);
	}
	i = -1;
	while (++i < main.threads_num)
		pthread_join(thread[i], NULL);
	free((void*)flows);
	free((void*)thread);
}

int			main(int ac, char **av)
{
	t_session	session;
	t_main		*main;
	int			fd;

	if (ac < 2 || (fd = open(av[1], O_RDONLY)) < 0)
		parse_error(ERROR_NOT_CORRECT_FILE);
	main = (t_main*)malloc(sizeof(t_main));
	main->ss_rays = 0;
	main->ss_ray_iter = 1;
	main->filter = 0;
	main->threads_num = 16;
	create_session(&session);
	parser(fd, main, &session);
	close(fd);
	thread(*main, &session);
	add_filter(main, &session);
	mlx_put_image_to_window(session.mlx, session.win, session.ini, 0, 0);
	mlx_hook(session.win, 2, 5, key_action, 0);
	mlx_hook(session.win, 17, 0, close_window, NULL);
	mlx_loop(session.mlx);
}
