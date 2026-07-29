
#include "../Include/cub3d.h"

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

size_t	ft_lentab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

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

char	**extract_map(char **av, t_game *game)
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
		return (NULL);
	while (1)
	{
		tab[j] = get_next_line(fd);
		if (tab[j] == NULL)
			break ;
		j++;
	}
	close(fd);
	tab[j] = NULL;
	game->map_height = len_fd;
	if (len_fd > 0)
		game->map_width = ft_strlen(tab[0]); 
	remove_newline(tab);
	return (tab);
}

void	init_direction(t_player *player, char c)
{
	if (c == 'N')
		player->angle = NORTH;
	if (c == 'S')
		player->angle = SOUTH;
	if (c == 'E')
		player->angle = EAST;
	if (c == 'W')
		player->angle = WEST;
}



int	find_pos(t_game *game)
{
	size_t	i;
	size_t	j;
	char	*charset;

	i = 0;
	charset = "NSEW";
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (find_player(game->map[i][j], charset))
			{
				game->player.pos_x = j * 64 + 32;
				game->player.pos_y = i * 64 + 32;
				init_direction(&game->player, game->map[i][j]);
				game->map[i][j] = '0';
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	delete_all_image(t_game *game)
{
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	return (0);
}

int	close_wind(t_game *game)
{
	delete_all_image(game);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	if (game->map)
		free_split(game->map);
	exit(0);
	return (0);
}

int	fill_data(t_game *game, char **av)
{
	game->player.game = game;
	game->map = extract_map(av, game);
	if (!game->map)
		return (1);
	player_initialisation(&game->player);
	if (find_pos(game) != 0)
		return (1);

	game->ceiling = 0x87CEEB;
	game->floor = 0x8B7355;

	game->east_cost = 0xFF0000;
	game->west_cost = 0xFFFF00;
	game->south_cost = 0x00FF00;
	game->north_cost = 0x0000FF;

	game->minimap.offset_x = 10;
	game->minimap.offset_y = 10;
	game->minimap.block_size = 10;

	game->mouse_x = MAX_WIDTH / 2;
	game->mouse_moving = 0;
	game->mouse_hidden = 0;

	return (0);
}

int	game_initiation(t_game *game, char **av)
{
	fill_data(game, av);
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_putstr_fd("Error\nMLX init failed\n", 2);
		exit(1);
	}
	game->win = mlx_new_window(game->mlx, MAX_WIDTH, MAX_HEIGHT, "Cube");
	if (!game->win)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
		return (1);
	}
	game->img = mlx_new_image(game->mlx, MAX_WIDTH, MAX_HEIGHT);
	if (!game->img)
		return (mlx_destroy_window(game->mlx, game->win),
			mlx_destroy_display(game->mlx), free(game->mlx), 1);
	game->data = mlx_get_data_addr(game->img, &game->bpp,
			&game->size_line, &game->endian);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

void	player_initialisation(t_player *player)
{
	player->angle = PI / 2;
	player->key_up = false;
	player->key_down = false;
	player->key_right = false;
	player->key_left = false;
	player->left_rotation = false;
	player->right_rotation = false;
}

// int	mouse_mvmt(int x,int y, t_game *game)
// {
// 	static int	last_x = -1;
// 	int			delta_x;

// 	(void)y;
// 	if (last_x == -1 )
// 	{
// 		last_x = x;
// 		return (0);
// 	}
// 	delta_x = x - last_x;
// 	game->player.angle += delta_x * MOUSE_SENS;
// 	if (game->player.angle > 2 * PI)
// 		game->player.angle -= 2 * PI;
// 	if (game->player.angle < 0)
// 		game->player.angle += 2 * PI;
// 	last_x = x;
// 	return (0);
// }

int mouse_mvmt(int x, int y, t_game *game)
{
    static int last_x = -1;
    int delta_x;
    int center_x = MAX_WIDTH / 2;
    int center_y = MAX_HEIGHT / 2;

    (void)y;
    if (x <= 5 || x >= MAX_WIDTH - 5 || y <= 5 || y >= MAX_HEIGHT - 5)
    {
        mlx_mouse_move(game->mlx, game->win, center_x, center_y);
        last_x = center_x;
        return (0);
    }
    if (last_x == -1)
    {
        last_x = x;
        return (0);
    }
	delta_x = x - last_x;
    game->player.angle += delta_x * MOUSE_SENS;
    if (game->player.angle > 2 * PI)
        game->player.angle -= 2 * PI;
    if (game->player.angle < 0)
        game->player.angle += 2 * PI;
    last_x = x;
    return (0);
}

void	released_key(int keycode, t_player *player)
{
	if (keycode == UP)
		player->key_up = false;
	else if (keycode == DOWN)
		player->key_down = false;
	else if (keycode == RIGHT)
		player->key_right = false;
	else if (keycode == LEFT)
		player->key_left = false;
	else if (keycode == ARR_LEFT)
		player->left_rotation = false;
	else if (keycode == ARR_RIGHT)
		player->right_rotation = false;
}

void	pressed_key(int keycode, t_game *game)
{
	if (keycode == ESC)
		close_wind(game);
	if (keycode == UP)
		game->player.key_up = true;
	else if (keycode == DOWN)
		game->player.key_down = true;
	else if (keycode == RIGHT)
		game->player.key_right = true;
	else if (keycode == LEFT)
		game->player.key_left = true;
	else if (keycode == ARR_LEFT)
		game->player.left_rotation = true;
	else if (keycode == ARR_RIGHT)
		game->player.right_rotation = true;
}

int is_wall(t_game *game, float x, float y)
{
	int map_x;
	int map_y;

	map_x = (int)(x / BITS_SIZE);
	map_y = (int)(y / BITS_SIZE);	
	if (map_x < 0 || map_x >= game->map_width || map_y < 0 || map_y >= game->map_height)
		return (1);
	return (game->map[map_y][map_x] == '1');
}

void	player_rotation(t_player *player, float speed_angle)
{
	if (player->left_rotation)
		player->angle -= speed_angle;
	if (player->right_rotation)
		player->angle += speed_angle;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
}

void player_translation(t_player *player, t_game *game, float cos_angle, float sin_angle)
{
	int speed;
	float new_x;
	float new_y;

	speed = 2;
	
	if (player->key_up)
	{
		new_x = player->pos_x + cos_angle * speed;
		new_y = player->pos_y + sin_angle * speed;
		
		if (!is_wall(game, new_x, player->pos_y))
			player->pos_x = new_x;
		if (!is_wall(game, player->pos_x, new_y))
			player->pos_y = new_y;
	}
	if (player->key_down)
	{
		new_x = player->pos_x - cos_angle * speed;
		new_y = player->pos_y - sin_angle * speed;
		
		if (!is_wall(game, new_x, player->pos_y))
			player->pos_x = new_x;
		if (!is_wall(game, player->pos_x, new_y))
			player->pos_y = new_y;
	}
	if (player->key_left)
	{
		new_x = player->pos_x + sin_angle * speed;
		new_y = player->pos_y - cos_angle * speed;
		
		if (!is_wall(game, new_x, player->pos_y))
			player->pos_x = new_x;
		if (!is_wall(game, player->pos_x, new_y))
			player->pos_y = new_y;
	}
	if (player->key_right)
	{
		new_x = player->pos_x - sin_angle * speed;
		new_y = player->pos_y + cos_angle * speed;
		
		if (!is_wall(game, new_x, player->pos_y))
			player->pos_x = new_x;
		if (!is_wall(game, player->pos_x, new_y))
			player->pos_y = new_y;
	}
}


void	player_mouvement(t_player *player)
{
	float	speed_angle;
	float	cos_angle;
	float	sin_angle;

	speed_angle = 0.03;
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	player_rotation(player, speed_angle);
	player_translation(player, player->game, cos_angle, sin_angle);
}

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

// void get_wall_orientation(t_raycast *ray)
// {
// 	float hit_x;
// 	float hit_y;
// 	int map_x;
// 	int map_y;

// 	//Convertir en index
// 	map_x = (int)(ray->x_ray / BITS_SIZE);
// 	map_y = (int)(ray->y_ray / BITS_SIZE);

// 	//trouver la position dans la map
// 	hit_x = ray->x_ray - map_x * BITS_SIZE;
// 	hit_y = ray->y_ray - map_y * BITS_SIZE;

// 	if (hit_y < 2 || hit_y > BITS_SIZE - 2) // 0 = nord et 64= sud
// 		ray->wall_orientation = SOUTH;
// 	else if (hit_x < 2 || hit_x > BITS_SIZE - 2) // env 0 = ouest et env64 = est ( y peut etre nimporte ou entre 0-64)
// 		ray->wall_orientation = WEST;
// 	else
// 		ray->wall_orientation = WEST;
// }


bool	touch(float pos_x, float pos_y, t_game *game)
{
	int	x;
	int	y;

	x = pos_x / BITS_SIZE;
	y = pos_y / BITS_SIZE;
	if (game->map[y][x] == '1')
		return (true);
	return (false);
}

float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

float	distance_fixed(float x_ray, float y_ray, t_game *game)
{
	float	x_delta;
	float	y_delta;
	float	angle;	
	float	dist_fixed;

	x_delta = x_ray - game->player.pos_x;
	y_delta = y_ray - game->player.pos_y;
	angle = atan2(y_delta, x_delta) - game->player.angle;
	dist_fixed = distance(x_delta, y_delta) * cos(angle);
	return (dist_fixed);
}




void	draw_column(t_game *game, int x, t_raycast *ray)
{
	int		y;
	int		wall_color;

	wall_color = game->west_cost; // valeur par defaut
	if (ray->wall_orientation == NORTH)
		wall_color = game->north_cost;
	else if (ray->wall_orientation == SOUTH)
		wall_color = game->south_cost;
	else if (ray->wall_orientation == EAST)
		wall_color = game->east_cost;
	else if (ray->wall_orientation == WEST)
		wall_color = game->west_cost;
	y = 0;
	while (y < ray->beg_y)
	{
		put_pixel(x, y, game->ceiling, game);
		y++;
	}
	while (y < ray->end)
	{
		put_pixel(x, y, wall_color, game);
		y++;
	}
	while (y < MAX_HEIGHT)
	{
		put_pixel(x, y, game->floor, game);
		y++;
	}
}

void	draw_line(t_player *player, t_game *game, float beg_x, int i)
{
	t_raycast	*raycast;

	raycast = &game->raycast;
	raycast->angle_cos = cos(beg_x);
	raycast->angle_sin = sin(beg_x);
	raycast->x_ray = player->pos_x;
	raycast->y_ray = player->pos_y;
	while (!touch(raycast->x_ray, raycast->y_ray, game))
	{
		raycast->x_ray += raycast->angle_cos;
		raycast->y_ray += raycast->angle_sin;
	}
	raycast->dist = distance_fixed(raycast->x_ray, raycast->y_ray, game);
	raycast->height = (BITS_SIZE / raycast->dist) * (MAX_WIDTH / 2);
	raycast->beg_y = (MAX_HEIGHT - raycast->height) / 2;
	raycast->end = raycast->beg_y + raycast->height;
	
	// get_wall_orientation(raycast);
	draw_column(game, i, raycast);
}

int	draw_loop(t_game *game)
{
	t_player	*player;
	float		fraction;
	float		x_start;
	int			i;

	player = &game->player;
	fraction = PI / 3 / MAX_WIDTH;
	x_start = player->angle - PI / 6;
	player_mouvement(player);

	i = 0;
	while (i < MAX_WIDTH)
	{
		draw_line(player, game, x_start, i);
		x_start += fraction;
		i++;
	}
	minimap(game); // BONUS
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}


// int	draw_loop(t_game *game)
// {
// 	t_player	*player;
// 	// float		fraction;
// 	// float		x_start;
// 	// int			i;

// 	player = &game->player;
// 	// fraction = PI / 3 / MAX_WIDTH;
// 	// x_start = player->angle - PI / 6;
// 	player_mouvement(player);

// 	// i = 0;
// 	// while (i < MAX_WIDTH)
// 	// {
// 	// 	draw_line(player, game, x_start, i);
// 	// 	x_start += fraction;
// 	// 	i++;
// 	// }
// 	minimap(game); // BONUS
// 	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
// 	return (0);
// }

int	main(int ac, char **av)
{
	t_game		game;

	(void)ac;
	game_initiation(&game, av);
	mlx_hook(game.win, 2, 1L << 0, (void *)pressed_key, &game);
	mlx_hook(game.win, 3, 1L << 1, (void *)released_key, &game.player);
	mlx_hook(game.win, 6, 1L << 6, (void *)mouse_mvmt, &game);
	mlx_hook((&game)->win, CLOSE_MOUSE, 0, (void *)close_wind, &game);
	mlx_loop_hook(game.mlx, (void *)draw_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
