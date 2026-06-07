/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-har <hoel-har@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 14:35:31 by hoel-har          #+#    #+#             */
/*   Updated: 2026/06/07 17:22:17 by hoel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	error_handling(int ac, char **av)
{
	int	len;

	if (ac != 2)
		return (printf(USAGE));
	len = ft_strlen(av[1]);
	if (av[1][len - 1] != 'b' && av[1][len - 2] != 'u' && av[1][len - 3] != 'c' && av[1][len - 4] != '.' )
		return (printf("Invalid file\n"));
	return (0);
}

int	data_extraction(int ac, char **av)
{
	(void)ac;
	char *line;
	int fd;
	
	fd = open(av[1], O_RDONLY);
	line = get_next_line(fd);
	if (!line)
		return (1);
	while (line != NULL)
	{
		printf("%s\n", line);
		free(line);
		line = get_next_line(fd);
	}
	
	close(fd);
	return (1);
}

int main (int ac, char **av)
{
	if (error_handling(ac, av) != 0)
		return (1);
	if (data_extraction(ac, av) != 0)
		return (1);
	return (0);
}