/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtodzzi <mtodzzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 11:38:11 by mtodzzi           #+#    #+#             */
/*   Updated: 2026/08/04 00:00:00 by mtodzzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

int	first_map_line(char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		if (!is_empty_line(lines[i]) && get_line_type(lines[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static int	count_map_len(char **lines, int start, int total)
{
	int	end;

	end = total;
	while (end > start && is_empty_line(lines[end - 1]))
		end--;
	return (end - start);
}

char	**build_map(char **lines, int start)
{
	char	**map;
	int		total;
	int		len;
	int		i;

	total = count_lines_arr(lines);
	len = count_map_len(lines, start, total);
	map = malloc(sizeof(char *) * (len + 1));
	if (!map)
		return (NULL);
	i = 0;
	while (i < len)
	{
		map[i] = ft_strdup(lines[start + i]);
		if (!map[i])
			return (free_line(map), NULL);
		i++;
	}
	map[i] = NULL;
	return (map);
}

int	set_map_size(t_data *data)
{
	int	i;
	int	len;

	data->map_height = count_lines_arr(data->map);
	data->map_width = 0;
	i = 0;
	while (i < data->map_height)
	{
		len = ft_strlen(data->map[i]);
		if (len > data->map_width)
			data->map_width = len;
		i++;
	}
	return (1);
}
