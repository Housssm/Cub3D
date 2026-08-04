/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtodzzi <mtodzzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 11:38:11 by mtodzzi           #+#    #+#             */
/*   Updated: 2026/08/04 00:00:00 by mtodzzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

int	is_white_space(char c)
{
	return (c == '\n' || c == '\t' || c == ' '
		|| c == '\r' || c == '\v' || c == '\f');
}

int	is_white_space_map(char c)
{
	return (c == '\t' || c == ' ' || c == '\r'
		|| c == '\v' || c == '\f');
}

void	free_line(char **line)
{
	int	i;

	if (!line)
		return ;
	i = 0;
	while (line[i])
	{
		free(line[i]);
		i++;
	}
	free(line);
}

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && is_white_space(line[i]))
		i++;
	return (line[i] == '\0');
}
