
#include "cub3d.h"


void	remove_newline(char **tab)
{
	int	i;
	int	j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (tab[i][j] == '\n')
				tab[i][j] = '\0';
			j++;
		}
		i++;
	}
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	size_fd(int fd)
{
	int		i;
	char	*str;

	i = 0;
	while (1)
	{
		str = get_next_line(fd);
		if (str == NULL)
			break ;
		i += 1;
		free(str);
	}
	close (fd);
	return (i);
}

char	**extract_map(char **av, t_data *data)
{
	int				fd;
	int				j;
	int				len_fd;
	char			**tab;

	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Check Rights\n", 1), NULL);
	len_fd = size_fd(fd);
	fd = open(av[1], O_RDONLY);
	j = 0;
	tab = malloc(sizeof(char *) * (len_fd + 1));
	if (!tab)
		return (free_tab(tab), NULL);
	while (1)
	{
		tab[j] = get_next_line(fd);
		if (tab[j] == NULL)
			break ;
		j++;
	}
	close(fd);
	tab[j] = NULL;
	data->map_height = len_fd;
	remove_newline(tab);
	return (tab);
}
void	fill_data(t_data *data, char **av)
{
	data->game->map = extract_map(av, data);
	data->map_width = ft_strlen(data->game->map[1]);
	data->game->w = data->map_width;
	data->game->h = data->map_height;
	data->wall = "images/wall.xpm";
	// data->game->w =data->map_height;
	// data->game->h = data->map_width;
	// data->game-> = data->n_text;
	// data->game-> = data->s_text;
	// data->game-> = data->w_text;
	// data->game-> = data->e_text;
	data->floor = "images/floor.xpm";
	data->playa = "images/perso.xpm";
	// data->game-> = data->c_color;
	
	// data->game->map = data->map;

	// data->mlx;
	// data->win;
	// data->img;
}
/*********************************************************************/
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

	data->game->wall = mlx_xpm_file_to_image(data->game->mlx, data->wall, &data->game->w, &data->game->h);
	data->game->floor = mlx_xpm_file_to_image(data->game->mlx, data->floor, &data->game->w, &data->game->h);
	data->game->player = mlx_xpm_file_to_image(data->game->mlx, data->playa, &data->game->w, &data->game->h);
	
	// data->game->north_texture = mlx_xpm_file_to_image(data->game->mlx, data->game->north_texture, &data->map_width, &data->map_height);
	// data->game->south_texture = mlx_xpm_file_to_image(data->game->mlx, data->game->south_texture, &data->map_width, &data->map_height);
	// data->game->east_texture = mlx_xpm_file_to_image(data->game->mlx, data->game->east_texture, &data->map_width, &data->map_height);
	// data->game->west_texture = mlx_xpm_file_to_image(data->game->mlx, data->game->west_texture, &data->map_width, &data->map_height);

	if (!data->game->wall || !data->game->floor || !data->game->player)
	{
		ft_putstr_fd("Error: Image loading failed\n", 2);
		return (1);
	}

	return (0);
}


int	fill_display(t_game *game, size_t i, size_t j)
{
	int	check;

	check = 0;

	if (game->map[i][j] == '1')
		check = mlx_put_image_to_window(game->mlx, game->win, game->wall, j * BITS_SIZE, i * BITS_SIZE);
	if (game->map[i][j] == '0')
		check = mlx_put_image_to_window(game->mlx, game->win, game->floor, j * BITS_SIZE, i * BITS_SIZE);	
	if (game->map[i][j] == 'P')
		check = mlx_put_image_to_window(game->mlx, game->win, game->player, j * BITS_SIZE, i * BITS_SIZE);
	else if (check == 0)
		return (1);

	return (0);
}

int	player_mouvement(t_data *data, int x, int y)
{
	int	pos_x;
	int	pos_y;

	pos_x = data->game->pos_x;
	pos_y = data->game->pos_y;
	if (data->game->map[pos_y + y][pos_x + x] != '1')
	{

		data->game->map[pos_y + y][pos_x + x] = 'P';
		data->game->map[pos_y][pos_x] = '0';
		data->game->pos_x += x;
		data->game->pos_y += y;
	}
	delete_all_image(data);
	display(data);
	return (0);
}

int	key_pressed(int touch,t_data *data)
{
	int	win;

	win = 0;
	count = 0;
	if (touch == ESC)
		close_wind(data);
	else if (touch == RIGHT)
		win = player_mouvement(data, 1, 0);
	else if (touch == LEFT)
		win = player_mouvement(data, -1, 0);
	else if (touch == UP)
		win = player_mouvement(data, 0, -1);
	else if (touch == DOWN)
		win = player_mouvement(data, 0, 1);
	if (win == 1 || win == 404)
	{
		if (win == 1)
			ft_putstr_fd("Victory\n", 1);
		else if (win == 404)
			ft_putstr_fd("You've been caught.", 1);
		close_wind(data);
	}
	return (0);
}

int	display(t_data *data)
{
	size_t	i;
	size_t	j;
	
	i = 0;
	if (file_to_img(data))
		return (close_wind(data), 1);
	while (data->game->map[i])
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
	// display_mouv(data);
	return (0);
}



int main(int ac, char **av)
{
	t_data	data;
	t_game	game;
	
	data.game = &game;
	(void)ac;
	fill_data(&data, av);
	
	if (wind_creation(&data))
		return (close_wind(&data) ,1);
	if (display(&data))
		return (close_wind(&data) ,1);
	mlx_hook((&data)->game->win, 2, 1L << 0, (void *)key_pressed, &data);
	mlx_hook((&data)->game->win, CLOSE_MOUSE, 0, (void *)close_wind, &data);
 	mlx_loop(data.game->mlx);
	return (0);
}
