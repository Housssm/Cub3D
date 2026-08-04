/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtodzzi <mtodzzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 11:38:11 by mtodzzi           #+#    #+#             */
/*   Updated: 2026/08/04 00:00:00 by mtodzzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

int	get_line_type(char *line)
{
	int	code;

	code = is_texture_id(line, 0);
	if (code != 0)
		return (code);
	code = is_color_id(line, 0);
	if (code == 1)
		return (5);
	if (code == 2)
		return (6);
	return (0);
}

int	parse_config_line(t_data *data, char *line)
{
	int	type;

	if (is_empty_line(line))
		return (1);
	type = get_line_type(line);
	if (type >= 1 && type <= 4)
		return (texture_path(&data->tex, line));
	if (type == 5 || type == 6)
		return (floor_or_ceilling(data, line));
	return (0);
}

int	parse_all_config(t_data *data, char **lines, int end)
{
	int	i;

	i = 0;
	while (i < end)
	{
		if (!parse_config_line(data, lines[i]))
			return (0);
		i++;
	}
	return (1);
}

int	all_config_set(t_data *data)
{
	if (!valide_texture(&data->tex))
		return (0);
	if (!data->floor_set || !data->ceiling_set)
		return (0);
	return (1);
}
