/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtodzzi <mtodzzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 11:38:11 by mtodzzi           #+#    #+#             */
/*   Updated: 2026/08/04 00:00:00 by mtodzzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

static int	report_error(char *msg)
{
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	return (0);
}

void	free_data(t_data *data)
{
	free_line(data->map);
	free(data->tex.no);
	free(data->tex.so);
	free(data->tex.we);
	free(data->tex.ea);
}

static int	build_scene(t_data *data, char **lines)
{
	int	start;

	start = first_map_line(lines);
	if (start < 0)
		return (report_error("No map found in the scene file\n"));
	if (!parse_all_config(data, lines, start))
		return (report_error("Invalid configuration line\n"));
	if (!all_config_set(data))
		return (report_error("Missing texture(s) or color(s)\n"));
	data->map = build_map(lines, start);
	if (!data->map)
		return (report_error("Map allocation failed\n"));
	return (1);
}

static int	validate_scene(t_data *data)
{
	set_map_size(data);
	if (!is_valid_map(data, data->map))
		return (report_error("Invalid character or player in map\n"));
	if (!is_close_map(data->map))
		return (report_error("Map is not closed\n"));
	if (!right_map(data, data->map))
		return (report_error("Map has a leak\n"));
	return (1);
}

int	parse_scene(t_data *data, char *file)
{
	char	**lines;

	if (!is_valide_file(file))
		return (0);
	lines = read_all_lines(file);
	if (!lines)
		return (report_error("Cannot read file\n"));
	if (!build_scene(data, lines) || !validate_scene(data))
	{
		free_line(lines);
		free_data(data);
		return (0);
	}
	free_line(lines);
	return (1);
}
