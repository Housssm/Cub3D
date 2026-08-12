#include "../Includes/cub3d.h"

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