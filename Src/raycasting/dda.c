/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-har <hoel-har@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/12 15:38:14 by hoel-har          #+#    #+#             */
/*   Updated: 2026/08/12 15:38:15 by hoel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= MAX_WIDTH || y >= MAX_HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

static float	delta_distance(float direction)
{
	if (fabs(direction) < 0.000001)
		return (1e30);
	return (fabs(1.0 / direction));
}

static void	set_x_step(t_raycast *raycast, float player_x)
{
	if (raycast->angle_cos < 0)
	{
		raycast->step_x = -1;
		raycast->side_dist_x = (player_x - raycast->map_x)
			* raycast->delta_dist_x;
	}
	else
	{
		raycast->step_x = 1;
		raycast->side_dist_x = (raycast->map_x + 1.0 - player_x)
			* raycast->delta_dist_x;
	}
}

static void	set_y_step(t_raycast *raycast, float player_y)
{
	if (raycast->angle_sin < 0)
	{
		raycast->step_y = -1;
		raycast->side_dist_y = (player_y - raycast->map_y)
			* raycast->delta_dist_y;
	}
	else
	{
		raycast->step_y = 1;
		raycast->side_dist_y = (raycast->map_y + 1.0 - player_y)
			* raycast->delta_dist_y;
	}
}

void	ray_initiation(t_player *player, t_raycast *raycast, int col)
{
	float	camera_x;
	float	direction_xy[2];
	float	plane_xy[2];
	float	player_x;
	float	player_y;

	ft_bzero(raycast, sizeof(*raycast));
	camera_x = 2.0 * col / (float)MAX_WIDTH - 1.0;
	direction_xy[0] = cos(player->angle);
	direction_xy[1] = sin(player->angle);
	plane_xy[0] = -direction_xy[1] * tan(PI / 6.0);
	plane_xy[1] = direction_xy[0] * tan(PI / 6.0);
	raycast->angle_cos = direction_xy[0] + plane_xy[0] * camera_x;
	raycast->angle_sin = direction_xy[1] + plane_xy[1] * camera_x;
	player_x = player->pos_x / BITS_SIZE;
	player_y = player->pos_y / BITS_SIZE;
	raycast->map_x = (int)player_x;
	raycast->map_y = (int)player_y;
	raycast->delta_dist_x = delta_distance(raycast->angle_cos);
	raycast->delta_dist_y = delta_distance(raycast->angle_sin);
	set_x_step(raycast, player_x);
	set_y_step(raycast, player_y);
}
