/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_cleaning.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-har <hoel-har@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 19:44:35 by hoel-har          #+#    #+#             */
/*   Updated: 2026/06/17 19:44:38 by hoel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



/********************CLEANING************************************/
int	delete_all_image(t_data *data)
{
	if (data->wall)
		mlx_destroy_image(data->mlx, data->wall);
	if (data->f_color)
		mlx_destroy_image(data->mlx, data->f_color);
	return (0);
}

int	close_wind(t_data *data)
{
	delete_all_image(data);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	if (data->map)
		free_tab(data->map);
	exit(0);
	return (0);
}
/****************************************** */