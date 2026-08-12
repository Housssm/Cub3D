/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtodzzi <mtodzzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 15:45:43 by mtodzzi           #+#    #+#             */
/*   Updated: 2026/08/04 00:00:00 by mtodzzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

int	is_valid_rgb(int *rgb)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (rgb[i] < 0 || rgb[i] > 255)
			return (0);
		i++;
	}
	return (1);
}

int	is_color_id(char *path, int index)
{
	if (path[index + 1] && !is_white_space(path[index + 1]))
		return (0);
	if (path[index] == 'F')
		return (1);
	else if (path[index] == 'C')
		return (2);
	return (0);
}

static int	extract_rgb(t_data *data, char *line, int code)
{
	int		i;
	char	**tab;
	int		*rgb;

	i = 1;
	while (line[i] && is_white_space_map(line[i]))
		i++;
	tab = count_rgb(line + i);
	if (!tab || !check_tab_rgb(tab))
		return (free_line(tab), 0);
	if (code == 1)
		rgb = data->floor_rgb;
	else
		rgb = data->ceiling_rgb;
	rgb[0] = ft_atoi(tab[0]);
	rgb[1] = ft_atoi(tab[1]);
	rgb[2] = ft_atoi(tab[2]);
	free_line(tab);
	return (is_valid_rgb(rgb));
}

int	floor_or_ceilling(t_data *data, char *line)
{
	int	code;

	code = is_color_id(line, 0);
	if (code == 0)
		return (0);
	if ((code == 1 && data->floor_set) || (code == 2 && data->ceiling_set))
		return (0);
	if (!extract_rgb(data, line, code))
		return (0);
	if (code == 1)
		data->floor_set = 1;
	else
		data->ceiling_set = 1;
	return (1);
}
