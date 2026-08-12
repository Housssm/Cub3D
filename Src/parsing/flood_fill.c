/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtodzzi <mtodzzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 11:38:11 by mtodzzi           #+#    #+#             */
/*   Updated: 2026/08/04 00:00:00 by mtodzzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

char	**copy_map(char **map)
{
	char	**copy;
	int		total;
	int		i;

	total = count_map_lines(map);
	copy = malloc(sizeof(char *) * (total + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < total)
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
			return (free_line(copy), NULL);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

int	flood_fill(char **copy, int y, int x)
{
	char	c;
	int		res;

	if (y < 0 || x < 0 || !copy[y])
		return (0);
	if (x >= (int)ft_strlen(copy[y]))
		return (0);
	c = copy[y][x];
	if (c == '1' || c == 'F')
		return (1);
	if (c == ' ')
		return (0);
	copy[y][x] = 'F';
	res = flood_fill(copy, y + 1, x);
	res = flood_fill(copy, y - 1, x) && res;
	res = flood_fill(copy, y, x + 1) && res;
	res = flood_fill(copy, y, x - 1) && res;
	return (res);
}

int	right_map(t_data *data, char **map)
{
	char	**copy;
	int		res;

	copy = copy_map(map);
	if (!copy)
		return (0);
	res = flood_fill(copy, data->player_y, data->player_x);
	free_line(copy);
	return (res);
}
