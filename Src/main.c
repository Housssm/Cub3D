/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtodzzi <mtodzzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 11:38:11 by mtodzzi           #+#    #+#             */
/*   Updated: 2026/08/04 00:00:00 by mtodzzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

static int	check_arguments(int ac, char **av)
{
	if (ac != 2)
	{
		write(2, USAGE, ft_strlen(USAGE));
		return (0);
	}
	if (!is_cub_file(av[1]))
	{
		write(2, "Error\nFile must have a .cub extension\n", 39);
		return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (!check_arguments(ac, av))
		return (1);
	init_data(&data);
	if (!parse_scene(&data, av[1]))
		return (1);
	printf("Parsing OK\n");
	printf("Map %dx%d, player at (%d,%d)\n", data.map_width,
		data.map_height, data.player_x, data.player_y);
	free_data(&data);
	return (0);
}
