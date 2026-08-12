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
	t_data		data;
	t_game		game;

	if (!check_arguments(ac, av))
		return (1);
	init_data(&data, &game);
	if (game_initiation(&game, &data, av))
		return (game_cleaning(&game), 1);
	mlx_hook(game.win, 2, 1L << 0, (void *)pressed_key, &game);
	mlx_hook(game.win, 3, 1L << 1, (void *)released_key, &game.player);
	mlx_hook(game.win, 6, 1L << 6, (void *)mouse_mvmt, &game);
	mlx_hook((&game)->win, CLOSE_MOUSE, 0, (void *)close_wind, &game);
	mlx_loop_hook(game.mlx, (void *)draw_loop, &game);
	mlx_loop(game.mlx);
	game_cleaning(&game);
	return (0);
}
