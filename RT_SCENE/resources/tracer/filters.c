/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 14:41:39 by ozhovnuv          #+#    #+#             */
/*   Updated: 2017/08/22 14:41:41 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rt.h"

void		neggative_filter(t_session *session)
{
	int i;

	i = 0;
	while (i < WIDTH * HEIGHT * 4)
	{
		session->data[i] = 255 - session->data[i];
		session->data[i + 1] = 255 - session->data[i + 1];
		session->data[i + 2] = 255 - session->data[i + 2];
		i = i + 4;
	}
}

void		black_white_filter(t_session *session)
{
	int i;
	int coef;

	i = 0;
	while (i < WIDTH * HEIGHT * 4)
	{
		coef = (session->data[i] * 0.07) +
				(session->data[i + 1] * 0.72) +
				(session->data[i + 2] * 0.21);
		session->data[i] = coef;
		session->data[i + 1] = coef;
		session->data[i + 2] = coef;
		i += 4;
	}
}

void		add_filter(t_main *main, t_session *ses)
{
	if (main->filter == FIL_NEG)
		neggative_filter(ses);
	else if (main->filter == FIL_B_W)
		black_white_filter(ses);
}
