/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtodzzi <mtodzzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 11:38:11 by mtodzzi           #+#    #+#             */
/*   Updated: 2026/08/04 00:00:00 by mtodzzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

int	find_player(t_data *data, int y, int x)
{
	char	c;

	c = data->map[y][x];
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		data->player_count++;
		if (data->player_count > 1)
			return (0);
		data->player_x = x;
		data->player_y = y;
	}
	return (1);
}

int	is_valid_char(t_data *data, char *line, int y)
{
	int	x;

	x = 0;
	while (line[x])
	{
		if (!ft_strchr(CUB_CHARSET, line[x]))
			return (0);
		if (ft_strchr("NSEW", line[x]) && !find_player(data, y, x))
			return (0);
		x++;
	}
	return (1);
}

int	is_valid_map(t_data *data, char **map)
{
	int	y;

	if (!map)
		return (0);
	y = 0;
	while (map[y])
	{
		if (!is_valid_char(data, map[y], y))
			return (0);
		y++;
	}
	if (data->player_count != 1)
		return (0);
	return (1);
}
