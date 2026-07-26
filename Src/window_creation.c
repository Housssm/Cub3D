#include "../Include/cub3d.h"


// int	wind_creation(t_data *data)
// {
// 	int	width;
// 	int	height;

// 	width = data->game->w * BITS_SIZE;
// 	height = data->game->h* BITS_SIZE;
// 	data->game->mlx = mlx_init();
// 	if (!data->game->mlx)
// 	{
// 		ft_putstr_fd("ERROR:Mlx init failed\n", 2);
// 		exit(1);
// 	}
// 	data->game->win = mlx_new_window(data->game->mlx, width, height, WIND_NAME);
// 	if (!data->game->win)
// 	{
// 		mlx_destroy_display(data->game->mlx);
// 		free(data->game->mlx);
// 		return (1);
// 	}
// 	return (0);
// }

// int	file_to_img(t_data	*data)
// {

// 	data->game->wall = mlx_xpm_file_to_image(data->game->mlx, data->wall, &data->game->w, &data->game->h);
// 	data->game->floor = mlx_xpm_file_to_image(data->game->mlx, data->floor, &data->game->w, &data->game->h);
// 	data->game->player = mlx_xpm_file_to_image(data->game->mlx, data->playa, &data->game->w, &data->game->h);
	
// 	// data->game->north_texture = mlx_xpm_file_to_image(data->game->mlx, data->game->north_texture, &data->map_width, &data->map_height);
// 	// data->game->south_texture = mlx_xpm_file_to_image(data->game->mlx, data->game->south_texture, &data->map_width, &data->map_height);
// 	// data->game->east_texture = mlx_xpm_file_to_image(data->game->mlx, data->game->east_texture, &data->map_width, &data->map_height);
// 	// data->game->west_texture = mlx_xpm_file_to_image(data->game->mlx, data->game->west_texture, &data->map_width, &data->map_height);

// 	if (!data->game->wall || !data->game->floor || !data->game->player)
// 	{
// 		ft_putstr_fd("Error: Image loading failed\n", 2);
// 		return (1);
// 	}

// 	return (0);
// }

// int	fill_display(t_game *game, size_t i, size_t j)
// {
// 	int	check;

// 	check = 0;
// 	if (game->map[i][j] == '1')
// 		check = mlx_put_image_to_window(game->mlx, game->win, game->wall, j * BITS_SIZE, i * BITS_SIZE);
// 	else if (game->map[i][j] == '0')
// 		check = mlx_put_image_to_window(game->mlx, game->win, game->floor, j * BITS_SIZE, i * BITS_SIZE);	
// 	else if (game->map[i][j] == 'N' || game->map[i][j] == 'S' || game->map[i][j] == 'E' || game->map[i][j] == 'W' || game->map[i][j] == 'P')
// 	{
// 		check = mlx_put_image_to_window(game->mlx , game->win, game->player, j * BITS_SIZE, i * BITS_SIZE);
// 	}
// 	else if (check == 0)
// 		return (1);

// 	return (0);
// }

// int display(t_data *data)
// {
//     size_t 	i;
//     size_t 	j;
// 	// int 	start_x;
// 	// int 	start_y;
// 	// int 	end_x;
// 	// int 	end_y;

//     i = 0;
//     if (file_to_img(data))
//         return (close_wind(data), 1);
//     while (data->game->map[i])
//     {
//         j = 0;
//         while (data->game->map[i][j])
//         {            
//             if (fill_display(data->game, i, j))
//                 return (close_wind(data), 1);
//             j++;
//         }
//         i++;
//     }
//     // start_x = data->game->pos_x * BITS_SIZE + BITS_SIZE / 2;
//     // start_y = data->game->pos_y * BITS_SIZE + BITS_SIZE / 2;
//     // end_x = start_x + 5 * BITS_SIZE;
//     // end_y = start_y;
//     // draw_line(data->game, start_x, start_y, end_x, end_y, 0xFFFFFF);
//     return (0);
// }






int	wind_creation(t_data *data)
{
	int	width;
	int	height;

	width = data->game->w * BITS_SIZE;
	height = data->game->h* BITS_SIZE;
	data->game->mlx = mlx_init();
	if (!data->game->mlx)
	{
		ft_putstr_fd("ERROR:Mlx init failed\n", 2);
		exit(1);
	}
	data->game->win = mlx_new_window(data->game->mlx, width, height, WIND_NAME);
	if (!data->game->win)
	{
		mlx_destroy_display(data->game->mlx);
		free(data->game->mlx);
		return (1);
	}
	return (0);
}

int	file_to_img(t_data	*data)
{
	if (!data || !data->game || !data->game->mlx)
		return (1);
	if (data->game->wall && data->game->floor && data->game->player_img)
		return (0);
	data->game->wall = mlx_xpm_file_to_image(data->game->mlx, data->wall, &data->game->w, &data->game->h);
	data->game->floor = mlx_xpm_file_to_image(data->game->mlx, data->floor, &data->game->w, &data->game->h);
	data->game->player_img = mlx_xpm_file_to_image(data->game->mlx, data->playa, &data->game->w, &data->game->h);
	if (!data->game->wall || !data->game->floor || !data->game->player_img)
	{
		ft_putstr_fd("Error: Image loading failed\n", 2);
		return (1);
	}

	return (0);
}

int fill_display(t_game *game, size_t i, size_t j)
{
    char cell;
    int check;

    cell = game->map[i][j];
    check = 0;
    
    if (cell == '1')
        check = mlx_put_image_to_window(game->mlx, game->win, game->wall, 
                                        j * BITS_SIZE, i * BITS_SIZE);
    else if (cell == '0')
        check = mlx_put_image_to_window(game->mlx, game->win, game->floor, 
                                        j * BITS_SIZE, i * BITS_SIZE);
    else if (cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
    {
        // Mettre le sol d'abord
        mlx_put_image_to_window(game->mlx, game->win, game->floor, 
                                j * BITS_SIZE, i * BITS_SIZE);
        // Puis le joueur par dessus
        check = mlx_put_image_to_window(game->mlx, game->win, game->player_img, 
                                        j * BITS_SIZE, i * BITS_SIZE);
        // Remplacer le caractère par '0' pour ne plus afficher le joueur ici
        game->map[i][j] = '0';
    }
    
    return (check != 0);
}

// int display(t_data *data)
// {
// 	size_t 	i;
// 	size_t 	j;

// 	i = 0;
// 	if (file_to_img(data))
// 		return (close_wind(data), 1);
// 	mlx_clear_window(data->game->mlx, data->game->win);
// 	while (data->game->map && data->game->map[i])
// 	{
// 		j = 0;
// 		while (data->game->map[i][j])
// 		{            
// 			if (fill_display(data->game, i, j))
// 				return (close_wind(data), 1);
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (0);
// }

void display_player(t_data *data)
{
    int x, y;
    
    x = (int)(data->player->pos_x * BITS_SIZE);
    y = (int)(data->player->pos_y * BITS_SIZE);
    
    mlx_put_image_to_window(data->game->mlx, data->game->win, 
                           data->game->player_img, x, y);
}

// Modifiez display pour appeler display_player après avoir affiché la carte
int display(t_data *data)
{
    size_t i;
    size_t j;
    static int images_loaded = 0;

    if (!images_loaded)
    {
        if (file_to_img(data))
            return (close_wind(data), 1);
        images_loaded = 1;
    }
    
    mlx_clear_window(data->game->mlx, data->game->win);
    
    // Afficher la carte
    i = 0;
    while (data->game->map && data->game->map[i])
    {
        j = 0;
        while (data->game->map[i][j])
        {
            if (fill_display(data->game, i, j))
                return (close_wind(data), 1);
            j++;
        }
        i++;
    }
    
    // Afficher le joueur à sa position actuelle
    display_player(data);
    
    return (0);
}





















