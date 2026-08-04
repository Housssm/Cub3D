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

char	**count_rgb(char *str)
{
	int		count;
	char	**array;

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

int	check_tab_rgb(char **array)
{
	int	i;
	int	j;

	i = 0;
	while (array[i])
	{
		j = 0;
		while (array[i][j])
		{
			if (!ft_isdigit(array[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
