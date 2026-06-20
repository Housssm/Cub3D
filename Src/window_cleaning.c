/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_cleaning.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-har <hoel-har@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 19:44:35 by hoel-har          #+#    #+#             */
/*   Updated: 2026/06/20 17:32:47 by hoel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/********************CLEANING************************************/
int	delete_all_image(t_data *data)
{
	if (data->game->wall)
		mlx_destroy_image(data->game->mlx, data->game->wall);
	if (data->game->floor)
		mlx_destroy_image(data->game->mlx, data->game->floor);
	if (data->game->player)
		mlx_destroy_image(data->game->mlx, data->game->player);

	return (0);
}

int close_wind(t_data *data)
{
    // t_data *data = (t_data *)param;
    
    delete_all_image(data);
    if (data->game->win)
        mlx_destroy_window(data->game->mlx, data->game->win);
    if (data->game->mlx)
    {
        mlx_destroy_display(data->game->mlx);
        free(data->game->mlx);
    }
    if (data->game->map)
        free_tab(data->game->map);
    exit(0);
    return (0);
}
/****************************************** */