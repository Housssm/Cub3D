#include "../Include/cub3d.h"

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
