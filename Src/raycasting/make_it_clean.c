/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_it_clean.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-har <hoel-har@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/12 15:38:05 by hoel-har          #+#    #+#             */
/*   Updated: 2026/08/12 15:38:06 by hoel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

static void	destroy_texture(t_game *game, t_texture *texture)
{
	if (game->mlx && texture->img)
	{
		mlx_destroy_image(game->mlx, texture->img);
		texture->img = NULL;
		texture->data = NULL;
	}
}

static void	destroy_all_textures(t_game *game)
{
	destroy_texture(game, &game->texture_east);
	destroy_texture(game, &game->texture_west);
	destroy_texture(game, &game->texture_north);
	destroy_texture(game, &game->texture_south);
}

static void	free_path_texture(t_game *game)
{
	if (game->texture_east.path)
		free(game->texture_east.path);
	if (game->texture_west.path)
		free(game->texture_west.path);
	if (game->texture_north.path)
		free(game->texture_north.path);
	if (game->texture_south.path)
		free(game->texture_south.path);
	game->texture_east.path = NULL;
	game->texture_west.path = NULL;
	game->texture_north.path = NULL;
	game->texture_south.path = NULL;
}

void	game_cleaning(t_game *game)
{
	if (!game)
		return ;
	destroy_all_textures(game);
	if (game->mlx && game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->mlx && game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	if (game->map)
		free_split(game->map);
	free_path_texture(game);
	game->img = NULL;
	game->win = NULL;
	game->mlx = NULL;
	game->map = NULL;
}

int	close_wind(t_game *game)
{
	game_cleaning(game);
	exit(0);
	return (0);
}
