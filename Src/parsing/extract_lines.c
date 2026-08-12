/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_lines.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtodzzi <mtodzzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 11:38:11 by mtodzzi           #+#    #+#             */
/*   Updated: 2026/08/04 00:00:00 by mtodzzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

static void	strip_newline(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

int	count_lines_arr(char **lines)
{
	int	count;

	count = 0;
	if (!lines)
		return (0);
	while (lines[count])
		count++;
	return (count);
}

static int	count_file_lines(char *file)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

char	**read_all_lines(char *file)
{
	char	**lines;
	int		fd;
	int		total;
	int		i;

	total = count_file_lines(file);
	if (total < 0)
		return (NULL);
	lines = malloc(sizeof(char *) * (total + 1));
	if (!lines)
		return (NULL);
	fd = open(file, O_RDONLY);
	i = 0;
	while (i < total)
	{
		lines[i] = get_next_line(fd);
		if (!lines[i])
			break ;
		strip_newline(lines[i]);
		i++;
	}
	lines[i] = NULL;
	close(fd);
	return (lines);
}
