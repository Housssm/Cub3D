#include "../Include/cub3d.h"

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

int	dda_application(t_game *game, t_raycast *raycast)
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
