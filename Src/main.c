
#include "../Include/cub3d.h"


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
	// data->game->pos_x = data->position_player_x;
	// data->game->pos_y = data->position_player_y;
	find_pos(data->game->map, &data->game->pos_x, &data->game->pos_y, &data->game->pa);
	data->game->pos_dx = cos(data->game->pa) * 5;
	data->game->pos_dy = sin(data->game->pa) * 5;
	// data->game->w =data->map_height;
	// data->game->h = data->map_width;
	// data->game-> = data->n_text;
	// data->game-> = data->s_text;
	// data->game-> = data->w_text;
	// data->game-> = data->e_text;
	
	data->floor = "images/floor.xpm";
	data->playa = "images/perso.xpm";
	// data->game->ceiling = data->c_color;
	// data->game->floor = data->c_color;
	
	// data->game->map = data->map;

	// data->mlx;
	// data->win;
	// data->img;
}

size_t	ft_lentab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	find_player(char c, char *charset)
{
	int i;

	i = 0;
	while(charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

int init_direction(char c)
{
	if (c == 'N')
		return (3 * PI/ 2);
	else if (c == 'S')
		return (PI / 2);
	else if (c == 'E')
		return (0);
	else if (c == 'W')
		return (PI);
	else
		return (0);
}

void	find_pos(char **tab, double *x, double *y, double *direction)
{
	size_t	i;
	int		j;
	char	*charset;

	i = 0;
	charset = "NSEW";
	while (i < ft_lentab(tab))
	{
		j = 0;
		while (tab[i][j])
		{
			if (find_player(tab[i][j], charset))
			{
					*x = j;
					*y = i;
					*direction = init_direction(tab[i][j]);
					return ;
			}
			j++;
		}
		i++;
	}
}
/*********************************************************************/


// void draw_line(t_game *game, int beginX, int beginY, int endX, int endY, int color)
// {
// 	double	dx;
// 	double	dy;
// 	double	sx;
// 	double	sy;
// 	double err;
// 	double e2;

// 	dx = abs(endX - beginX);
// 	dy = abs(endY - beginY);
// 	err = dx - dy;
// 	if (beginX < endX)
// 		sx = 1;
// 	else
// 		sx = -1;
// 	if (beginY < endY)
// 		sy = 1;
// 	else
// 		sy = -1;
// 	while(1)
// 	{
// 		mlx_pixel_put(game->mlx, game->win, beginX, beginY, color);
// 		if (beginX == endX && beginY == endY)
// 			break;
// 		e2 = 2 * err;
// 		if (e2 > -dy)
// 		{
// 			err -= dy;
// 			beginX += sx;
// 		}
// 		if (e2 < dx)
// 		{
// 			err += dx;
// 			beginY += sy;
// 		}
// 	}
// }

int	key_pressed(int touch,t_data *data)
{
	double	win;
	// t_game	*game;

	// game = &data->game;
	win = 0;
	if (touch == ESC)
		close_wind(data);
	else if (touch == LEFT)
	{
		printf("LEFT");
		data->game->pa -= 0.1;
		if (data->game->pa < 0)
			data->game->pa += 2 * PI;
		data->game->pos_dx = cos(data->game->pa) * 5;
		data->game->pos_dy = sin(data->game->pa) * 5;
	}
	else if (touch == RIGHT)
	{
		printf("RIGHT");
		data->game->pa += 0.1;
		if (data->game->pa > 2 * PI)
			data->game->pa -= 2 * PI;
		data->game->pos_dx = cos(data->game->pa) * 5;
		data->game->pos_dy = sin(data->game->pa) * 5;
	}
	else if (touch == UP)
	{
		printf("UP");
		data->game->pos_x += data->game->pos_dx;
		data->game->pos_y += data->game->pos_dy;
	}
	else if (touch == DOWN)
	{
		printf("DOWN");
		data->game->pos_x -= data->game->pos_dx;
		data->game->pos_y -= data->game->pos_dy;
	}
	if (win == 1 || win == 404)
	{
		if (win == 1)
			ft_putstr_fd("Victory\n", 1);
		else if (win == 404)
			ft_putstr_fd("You've been caught.", 1);
		close_wind(data);
	}
	delete_all_image(data);
	display(data);
	return (0);
}

int main(int ac, char **av)
{
	t_data	data;
	t_game	game;
	// t_player	player;

	game.mlx = NULL;
	game.win = NULL;
	game.map = NULL;
	game.wall = NULL;
	game.floor = NULL;
	game.player = NULL;
	data.game = &game;
	// game.player = &player;
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
