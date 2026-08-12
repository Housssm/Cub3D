/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-har <hoel-har@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/12 15:37:57 by hoel-har          #+#    #+#             */
/*   Updated: 2026/08/12 15:39:14 by hoel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

static int	parse_color(int rgb[3])
{
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

int	extract_scene(t_game *game, t_data *data)
{
	game->map = data->map;
	game->map_height = data->map_height;
	game->map_width = data->map_width;
	game->player.pos_x = data->player_x * BITS_SIZE + BITS_SIZE / 2.0f;
	game->player.pos_y = data->player_y * BITS_SIZE + BITS_SIZE / 2.0f;
	game->player.angle = data->player_orientation;
	game->texture_north.path = data->tex.no;
	game->texture_south.path = data->tex.so;
	game->texture_west.path = data->tex.we;
	game->texture_east.path = data->tex.ea;
	game->floor = parse_color(data->floor_rgb);
	game->ceiling = parse_color(data->ceiling_rgb);
	return (0);
}
