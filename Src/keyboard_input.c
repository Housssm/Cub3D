#include "../Include/cub3d.h"

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
