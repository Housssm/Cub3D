/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtodzzi <mtodzzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 00:00:00 by mtodzzi           #+#    #+#             */
/*   Updated: 2026/08/04 00:00:00 by mtodzzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

static int	has_consecutive_commas(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ',' && str[i + 1] == ',')
			return (1);
		i++;
	}
	return (0);
}

char	**count_rgb(char *str)
{
	int		count;
	int		i;
	char	**array;

	i = 0;
	if (has_consecutive_commas(str))
		return (NULL);
	array = ft_split(str, ',');
	if (!array)
		return (NULL);
	count = 0;
	while (array[count])
		count++;
	if (count != 3)
	{
		free_line(array);
		return (NULL);
	}
	return (array);
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
