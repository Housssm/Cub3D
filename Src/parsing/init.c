/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtodzzi <mtodzzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 11:38:11 by mtodzzi           #+#    #+#             */
/*   Updated: 2026/08/04 00:00:00 by mtodzzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

void	init_data(t_data *data, t_game *game)
{
	data->map = NULL;
	data->map_height = 0;
	data->map_width = 0;
	data->player_x = -1;
	data->player_y = -1;
	data->player_count = 0;
	data->player_orientation = 0;
	data->tex.no = NULL;
	data->tex.so = NULL;
	data->tex.we = NULL;
	data->tex.ea = NULL;
	data->floor_rgb[0] = -1;
	data->floor_rgb[1] = -1;
	data->floor_rgb[2] = -1;
	data->ceiling_rgb[0] = -1;
	data->ceiling_rgb[1] = -1;
	data->ceiling_rgb[2] = -1;
	data->floor_set = 0;
	data->ceiling_set = 0;
	ft_bzero(game, sizeof(t_game));
	ft_bzero(&game->texture_east, sizeof(t_texture));
	ft_bzero(&game->texture_west, sizeof(t_texture));
	ft_bzero(&game->texture_north, sizeof(t_texture));
	ft_bzero(&game->texture_south, sizeof(t_texture));
}
