#include "../Include/cub3d.h"

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
