/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_closed.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtodzzi <mtodzzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 11:38:11 by mtodzzi           #+#    #+#             */
/*   Updated: 2026/08/04 00:00:00 by mtodzzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

int	count_map_lines(char **map)
{
	int	count;

	count = 0;
	if (!map)
		return (0);
	while (map[count])
		count++;
	return (count);
}

int	check_walls(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (line[i] != '1' && line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	is_close_map(char **map)
{
	int	total;

	total = count_map_lines(map);
	if (total == 0)
		return (0);
	if (!check_walls(map[0]) || !check_walls(map[total - 1]))
		return (0);
	return (1);
}
