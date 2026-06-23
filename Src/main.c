
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
	find_pos(data->game->map, &data->game->pos_x, &data->game->pos_y);
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


void	find_pos(char **tab, int *x, int *y)
{
	size_t	i;
	int		j;
	char	*charset;

	i = 0;
	charset = "NSEWP";
	while (i < ft_lentab(tab))
	{
		j = 0;
		while (tab[i][j])
		{
			if (find_player(tab[i][j], charset))
			{
					*x = j;
					*y = i;
					return ;
			}
			j++;
		}
		i++;
	}
}
/*********************************************************************/

// int draw_line(t_game *game, int beginX, int beginY, int endX, int endY, int color)
// {
// 	int	x;
// 	int	y;

// 	y = 0;
// 	while (game->map[y])
// 	{
// 		x = 0;
// 		while (game->map[y][x])
// 		{			
// 			if (x >= beginX && x <= endX)
// 				mlx_pixel_put(game->mlx, game->win, 50, 50, color);
// 			if (y >= beginY && y <= endY)
// 				mlx_pixel_put(game->mlx, game->win, 50, 50, color);
// 			x++;
// 		}
// 		y++;
// 	}

// 	return (0);
// }


void diaw_line(t_game *game, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;
    int e2;
    
    while (1)
    {
        // Dessiner un pixel
        mlx_pixel_put(game->mlx, game->win, x0, y0, color);
        
        // Condition d'arrêt
        if (x0 == x1 && y0 == y1)
            break;
        
        // Calcul de l'erreur
        e2 = 2 * err;
        
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void draw_line(t_game *game, int beginX, int beginY, int endX, int endY, int color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int err;
	int e2;

	dx = abs(endX - beginX);
	dy = abs(endY - beginY);
	err = dx - dy;
	if (beginX < endX)
		sx = 1;
	else
		sx = -1;
	if (beginY < endY)
		sy = 1;
	else
		sy = -1;
	while(1)
	{
		mlx_pixel_put(game->mlx, game->win, beginX, beginY, color);
		if (beginX == endX && beginY == endY)
			break;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			beginX += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			beginY += sy;
		}
	}
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
