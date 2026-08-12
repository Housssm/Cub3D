/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtodzzi <mtodzzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 11:38:11 by mtodzzi           #+#    #+#             */
/*   Updated: 2026/08/04 00:00:00 by mtodzzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

char	*get_texture_path(char *path)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	while (path && path[i] && is_white_space(path[i]))
		i++;
	if (path[i] == '/' || path[i] == '.')
		str = ft_strdup(path + i);
	return (str);
}

int	is_texture_id(char *path, int index)
{
	if (path[index + 2] && !is_white_space(path[index + 2]))
		return (0);
	if (path[index] == 'N' && path[index + 1] == 'O')
		return (1);
	else if (path[index] == 'S' && path[index + 1] == 'O')
		return (2);
	else if (path[index] == 'W' && path[index + 1] == 'E')
		return (3);
	else if (path[index] == 'E' && path[index + 1] == 'A')
		return (4);
	return (0);
}

static int	assign_texture(t_texture *tex, int which, char *path)
{
	char	*value;

	value = get_texture_path(path + 2);
	if (!value)
		return (0);
	if (which == 1 && !tex->no)
		tex->no = value;
	else if (which == 2 && !tex->so)
		tex->so = value;
	else if (which == 3 && !tex->we)
		tex->we = value;
	else if (which == 4 && !tex->ea)
		tex->ea = value;
	else
	{
		free(value);
		return (0);
	}
	return (1);
}

int	texture_path(t_texture *tex, char *path)
{
	int	which;

	which = is_texture_id(path, 0);
	if (!which)
		return (0);
	return (assign_texture(tex, which, path));
}

int	valide_texture(t_texture *tex)
{
	if (!tex->no || !tex->so || !tex->ea || !tex->we)
		return (0);
	if (!is_valide_file(tex->no) || !is_valide_file(tex->so)
		|| !is_valide_file(tex->ea) || !is_valide_file(tex->we))
		return (0);
	return (1);
}
