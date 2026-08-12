/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_initiation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-har <hoel-har@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/12 15:38:09 by hoel-har          #+#    #+#             */
/*   Updated: 2026/08/12 15:57:44 by hoel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

static int	charge_texture(t_game *game, t_texture *texture)
{
	texture->img = mlx_xpm_file_to_image(game->mlx, texture->path,
			&texture->width, &texture->height);
	if (!texture->img)
	{
		ft_putstr_fd("Error\nUnable to load the texture: ", 2);
		ft_putendl_fd(texture->path, 2);
		return (1);
	}
	texture->data = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->size_line, &texture->endian);
	if (!texture->data)
	{
		ft_putstr_fd("Error\nUnable to load the texture: ", 2);
		ft_putendl_fd(texture->path, 2);
		return (1);
	}
	return (0);
}

static int	charge_all_textures(t_game *game)
{
	if (charge_texture(game, &game->texture_east))
		return (1);
	if (charge_texture(game, &game->texture_west))
		return (1);
	if (charge_texture(game, &game->texture_north))
		return (1);
	if (charge_texture(game, &game->texture_south))
		return (1);
	return (0);
}

static void	player_initialisation(t_player *player)
{
	player->key_up = false;
	player->key_down = false;
	player->key_right = false;
	player->key_left = false;
	player->left_rotation = false;
	player->right_rotation = false;
}

static int	fill_data(t_game *game, t_data *data)
{
	game->player.game = game;
	if (extract_scene(game, data))
		return (1);
	player_initialisation(&game->player);
	game->minimap.offset_x = 10;
	game->minimap.offset_y = 10;
	game->minimap.block_size = 10;
	game->mouse_x = MAX_WIDTH / 2;
	game->mouse_moving = 0;
	game->mouse_hidden = 0;
	return (0);
}

int	game_initiation(t_game *game, t_data *data)
{
	if (fill_data(game, data))
		return (1);
	game->mlx = mlx_init();
	if (!game->mlx)
		return (ft_putstr_fd("Error\nMLX init failed\n", 2), 1);
	if (charge_all_textures(game))
		return (1);
	game->win = mlx_new_window(game->mlx, MAX_WIDTH, MAX_HEIGHT, WIND_NAME);
	if (!game->win)
		return (ft_putstr_fd("Error\nWindow creation failed\n", 2), 1);
	game->img = mlx_new_image(game->mlx, MAX_WIDTH, MAX_HEIGHT);
	if (!game->img)
		return (ft_putstr_fd("Error\nImage creation failed\n", 2), 1);
	game->data = mlx_get_data_addr(game->img, &game->bpp,
			&game->size_line, &game->endian);
	if (!game->data)
		return (ft_putstr_fd("Error\nImage address failed\n", 2), 1);
	return (0);
}
