/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_parse_func.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 16:36:01 by ozhovnuv          #+#    #+#             */
/*   Updated: 2017/08/21 16:36:03 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rt.h"

char	*first_word(char *str)
{
	int		start_pos;
	int		end_pos;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] > 40)
		{
			start_pos = i;
			break ;
		}
		i++;
	}
	end_pos = ft_strlen(str);
	while (str[i])
	{
		if (str[i] < 40 || !str[i + 1])
		{
			end_pos = i;
			break ;
		}
		i++;
	}
	return (ft_strsub(str, start_pos, end_pos - start_pos));
}

int		arraylen(char **array)
{
	int i;

	i = 0;
	if (array == NULL)
		return (0);
	while (array[i])
	{
		i++;
	}
	return (i);
}

int		strint(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '-')
			return (0);
		i++;
	}
	return (1);
}

int		strdouble(char *str)
{
	int i;
	int	flag;

	flag = 0;
	i = 0;
	if (str[0] && str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] == '.' && flag == 1)
			return (0);
		else if (str[i] == '.' && flag == 0)
			flag = 1;
		else if (!ft_isalnum(str[i]))
			return (0);
		i++;
	}
	if (i < 1)
		return (0);
	return (1);
}

double	atod(char *str)
{
	char	**doub;
	double	num;

	if (strint(str))
		return ((double)ft_atoi(str));
	if (!strdouble(str))
		parse_error(ERROR_NUM_NOT_CORRECT);
	doub = ft_strsplit(str, '.');
	if (arraylen(doub) != 2)
		parse_error(ERROR_NUMBER_NOT_EXIST);
	num = (double)abs(ft_atoi(doub[0]));
	num += (double)ft_atoi(doub[1]) / pow(10, ft_strlen(doub[1]));
	if (doub[0][0] == '-')
	{
		free_str_array(doub, 2);
		return (-num);
	}
	free_str_array(doub, 2);
	return (num);
}
