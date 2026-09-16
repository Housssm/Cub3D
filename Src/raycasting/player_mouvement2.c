/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mouvement2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtodzzi <mtodzzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 16:36:45 by mtodzzi           #+#    #+#             */
/*   Updated: 2026/09/16 16:37:06 by mtodzzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void	player_mouvement(t_player *player)
{
	float	speed_angle;
	float	cos_angle;
	float	sin_angle;

	speed_angle = 0.03;
	player_rotation(player, speed_angle);
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	player_translation(player, player->game, cos_angle, sin_angle);
}
