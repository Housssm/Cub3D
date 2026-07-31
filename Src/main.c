#include "../Include/cub3d.h"

static void	destroy_texture(t_game *game, t_texture *texture)
{
	if (game->mlx && texture->img)
	{
		mlx_destroy_image(game->mlx, texture->img);
		texture->img = NULL;
		texture->data = NULL;
	}
}

void	destroy_all_textures(t_game *game)
{
	destroy_texture(game, &game->texture_east);
	destroy_texture(game, &game->texture_west);
	destroy_texture(game, &game->texture_north);
	destroy_texture(game, &game->texture_south);
}

void	free_path_texture(t_game *game)
{
	free(game->texture_east.path);
	free(game->texture_west.path);
	free(game->texture_north.path);
	free(game->texture_south.path);
	game->texture_east.path = NULL;
	game->texture_west.path = NULL;
	game->texture_north.path = NULL;
	game->texture_south.path = NULL;
}

void	game_cleaning(t_game *game)
{
	if (!game)
		return ;
	destroy_all_textures(game);
	if (game->mlx && game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->mlx && game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	if (game->map)
		free_split(game->map);
	free_path_texture(game);
	game->img = NULL;
	game->win = NULL;
	game->mlx = NULL;
	game->map = NULL;
}

int	close_wind(t_game *game)
{
	game_cleaning(game);
	exit(0);
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

int	fill_data(t_game *game, char **av)
{
	game->player.game = game;
	if (extract_scene(av, game))
		return (1);
	if (!game->map)
		return (1);
	player_initialisation(&game->player);
	game->ceiling = 0x87CEEB;
	game->minimap.offset_x = 10;
	game->minimap.offset_y = 10;
	game->minimap.block_size = 10;
	game->mouse_x = MAX_WIDTH / 2;
	game->mouse_moving = 0;
	game->mouse_hidden = 0;
	return (0);
}

static int	game_initiation(t_game *game, char **av)
{
	if (fill_data(game, av))
		return (1);
	game->mlx = mlx_init();
	if (!game->mlx)
		return (ft_putstr_fd("Error\nMLX init failed\n", 2), 1);
	if (charge_all_textures(game))
		return (1);
	game->win = mlx_new_window(game->mlx, MAX_WIDTH, MAX_HEIGHT, WIND_NAME);
	if (!game->win)
		return (ft_putstr_fd("Error\nWindow creation failed\n", 2), 1);
	game->img = mlx_new_image(game->mlx, MAX_WIDTH, MAX_HEIGHT);
	if (!game->img)
		return (ft_putstr_fd("Error\nImage creation failed\n", 2), 1);
	game->data = mlx_get_data_addr(game->img, &game->bpp,
			&game->size_line, &game->endian);
	if (!game->data)
		return (ft_putstr_fd("Error\nImage address failed\n", 2), 1);
	return (0);
}

int	mouse_mvmt(int x, int y, t_game *game)
{
	static int	last_x = -1;

	if (x <= 5 || x >= MAX_WIDTH - 5 || y <= 5 || y >= MAX_HEIGHT - 5)
	{
		mlx_mouse_move(game->mlx, game->win, MAX_WIDTH / 2, MAX_HEIGHT / 2);
		last_x = MAX_WIDTH / 2;
		return (0);
	}
	if (last_x == -1)
	{
		last_x = x;
		return (0);
	}
	game->player.angle += (x - last_x) * MOUSE_SENS;
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

int	is_wall(t_game *game, float x, float y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / BITS_SIZE);
	map_y = (int)(y / BITS_SIZE);
	if (map_x < 0 || map_x >= game->map_width || map_y < 0
		|| map_y >= game->map_height)
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
		player->angle -= 2 * PI;
	if (player->angle < 0)
		player->angle += 2 * PI;
}

void	move_to(t_player *player, t_game *game, float x, float y)
{
	if (!is_wall(game, x, player->pos_y))
		player->pos_x = x;
	if (!is_wall(game, player->pos_x, y))
		player->pos_y = y;
}

void	player_translation(t_player *player, t_game *game, float cos_angle,
		float sin_angle)
{
	int	speed;

	speed = 2;
	if (player->key_up)
		move_to(player, game, player->pos_x + cos_angle * speed,
			player->pos_y + sin_angle * speed);
	if (player->key_down)
		move_to(player, game, player->pos_x - cos_angle * speed,
			player->pos_y - sin_angle * speed);
	if (player->key_left)
		move_to(player, game, player->pos_x + sin_angle * speed,
			player->pos_y - cos_angle * speed);
	if (player->key_right)
		move_to(player, game, player->pos_x - sin_angle * speed,
			player->pos_y + cos_angle * speed);
}

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

void	get_wall_orientation(t_raycast *ray)
{
	float	hit_x;
	float	hit_y;
	int		map_x;
	int		map_y;

	map_x = (int)(ray->x_ray / BITS_SIZE);
	map_y = (int)(ray->y_ray / BITS_SIZE);
	hit_x = ray->x_ray - map_x * BITS_SIZE;
	hit_y = ray->y_ray - map_y * BITS_SIZE;
	if (hit_y < 2 || hit_y > BITS_SIZE - 2)
		ray->wall_orientation = SOUTH;
	else if (hit_x < 2 || hit_x > BITS_SIZE - 2)
		ray->wall_orientation = WEST;
	else
		ray->wall_orientation = WEST;
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

void	wall_delimitation(t_raycast *raycast)
{
	raycast->height = MAX_HEIGHT / raycast->distance;
	if (raycast->height < 1.0)
		raycast->height = 1.0;
	raycast->beg_y = (int)(-raycast->height / 2.0 + MAX_HEIGHT / 2.0);
	if (raycast->beg_y < 0)
		raycast->beg_y = 0;
	raycast->end = (int)(raycast->height / 2.0 + MAX_HEIGHT / 2.0);
	if (raycast->end > MAX_HEIGHT)
		raycast->end = MAX_HEIGHT;
}

void	set_text_x(t_game *game, t_raycast *raycast, t_texture *texture)
{
	float	player_x;
	float	player_y;

	player_x = game->player.pos_x / BITS_SIZE;
	player_y = game->player.pos_y / BITS_SIZE;
	if (raycast->side == SIDE_X)
		raycast->wall_x = player_y + raycast->distance * raycast->angle_sin;
	else
		raycast->wall_x = player_x + raycast->distance * raycast->angle_cos;
	raycast->wall_x -= floor(raycast->wall_x);
	raycast->texture_x = (int)(raycast->wall_x * texture->width);
	if ((raycast->side == SIDE_X && raycast->angle_cos > 0)
		|| (raycast->side == SIDE_Y && raycast->angle_sin < 0))
		raycast->texture_x = texture->width - raycast->texture_x - 1;
}

/////////////////////////////////

int	charge_texture(t_game *game, t_texture *texture)
{
	texture->img = mlx_xpm_file_to_image(game->mlx, texture->path,
			&texture->width, &texture->height);
	if (!texture->img)
	{
		ft_putstr_fd("Error\nUnable to load the texture: ", 2);
		ft_putendl_fd(texture->path, 2);
		return (1);
	}
	texture->data = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->size_line, &texture->endian);
	if (!texture->data)
	{
		ft_putstr_fd("Error\nUnable to load the texture: ", 2);
		ft_putendl_fd(texture->path, 2);
		return (1);
	}
	return (0);
}

int	charge_all_textures(t_game *game)
{
	if (charge_texture(game, &game->texture_east))
		return (1);
	if (charge_texture(game, &game->texture_west))
		return (1);
	if (charge_texture(game, &game->texture_north))
		return (1);
	if (charge_texture(game, &game->texture_south))
		return (1);
	return (0);
}

t_texture	*get_wall_texture(t_game *game, t_raycast *raycast)
{
	if (raycast->side == SIDE_X && raycast->angle_cos > 0)
		return (&game->texture_west);
	if (raycast->side == SIDE_X)
		return (&game->texture_east);
	if (raycast->angle_sin > 0)
		return (&game->texture_north);
	else
		return (&game->texture_south);
}

int	texture_pixel(t_texture *texture, int x, int y)
{
	char	*pixel;

	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x >= texture->width)
		x = texture->width - 1;
	if (y >= texture->height)
		y = texture->height - 1;
	pixel = texture->data + y * texture->size_line
		+ x * (texture->bpp / 8);
	return (*(unsigned int *)pixel);
}

void	draw_texture(t_game *game, t_raycast *raycast,
			t_texture *texture, int x)
{
	float	step;
	float	texture_position;
	int		texture_y;
	int		y;

	step = texture->height / raycast->height;
	texture_position = (raycast->beg_y - MAX_HEIGHT / 2.0
			+ raycast->height / 2.0) * step;
	y = raycast->beg_y;
	while (y < raycast->end)
	{
		texture_y = (int)texture_position;
		put_pixel(x, y, texture_pixel(texture,
				raycast->texture_x, texture_y), game);
		texture_position += step;
		y++;
	}
}
//////////////////////////////////////////////////

void	draw_column(t_game *game, int x, t_raycast *raycast)
{
	t_texture	*texture;
	int			y;

	wall_delimitation(raycast);
	texture = get_wall_texture(game, raycast);
	set_text_x(game, raycast, texture);
	y = 0;
	while (y < raycast->beg_y)
		put_pixel(x, y++, game->ceiling, game);
	draw_texture(game, raycast, texture, x);
	y = raycast->end;
	while (y < MAX_HEIGHT)
		put_pixel(x, y++, game->floor, game);
}

/*********************RAYCAST**********************/

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

static float	delta_distance(float direction)
{
	if (fabs(direction) < 0.000001)
		return (1e30);
	return (fabs(1.0 / direction));
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

static int	outside_map(t_game *game, int x, int y)
{
	if (y < 0 || y >= game->map_height || x < 0)
		return (1);
	if (x >= (int)ft_strlen(game->map[y]))
		return (1);
	return (0);
}

static int	perform_dda_loop(t_game *game, t_raycast *raycast)
{
	while (1)
	{
		if (raycast->side_dist_x < raycast->side_dist_y)
		{
			raycast->side_dist_x += raycast->delta_dist_x;
			raycast->map_x += raycast->step_x;
			raycast->side = SIDE_X;
		}
		else
		{
			raycast->side_dist_y += raycast->delta_dist_y;
			raycast->map_y += raycast->step_y;
			raycast->side = SIDE_Y;
		}
		if (outside_map(game, raycast->map_x, raycast->map_y))
			return (1);
		if (game->map[raycast->map_y][raycast->map_x] == '1'
			|| game->map[raycast->map_y][raycast->map_x] == ' ')
			return (0);
	}
}

static int	dda_application(t_game *game, t_raycast *raycast)
{
	if (perform_dda_loop(game, raycast))
		return (1);
	if (raycast->side == SIDE_X)
		raycast->distance = raycast->side_dist_x - raycast->delta_dist_x;
	else
		raycast->distance = raycast->side_dist_y - raycast->delta_dist_y;
	if (raycast->distance < 0.0001)
		raycast->distance = 0.0001;
	return (0);
}

void	draw_empty_column(t_game *game, int x)
{
	int	y;

	y = 0;
	while (y < MAX_HEIGHT)
	{
		if (y < MAX_HEIGHT / 2)
			put_pixel(x, y, game->ceiling, game);
		else
			put_pixel(x, y, game->floor, game);
		y++;
	}
}

void	draw_line(t_player *player, t_game *game, int x)
{
	t_raycast	*raycast;

	raycast = &game->raycast;
	ray_initiation(player, raycast, x);
	if (dda_application(game, raycast))
		draw_empty_column(game, x);
	else
		draw_column(game, x, raycast);
}

int	draw_loop(t_game *game)
{
	int			i;

	player_mouvement(&game->player);
	i = 0;
	while (i < MAX_WIDTH)
	{
		draw_line(&game->player, game, i);
		i++;
	}
	minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_game		game;

	(void)ac;
	ft_bzero(&game, sizeof(game));
	if (game_initiation(&game, av))
		return (game_cleaning(&game), 1);
	mlx_hook(game.win, 2, 1L << 0, (void *)pressed_key, &game);
	mlx_hook(game.win, 3, 1L << 1, (void *)released_key, &game.player);
	mlx_hook(game.win, 6, 1L << 6, (void *)mouse_mvmt, &game);
	mlx_hook((&game)->win, CLOSE_MOUSE, 0, (void *)close_wind, &game);
	mlx_loop_hook(game.mlx, (void *)draw_loop, &game);
	mlx_loop(game.mlx);
	game_cleaning(&game);
	return (0);
}
