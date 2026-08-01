#include "../Include/cub3d.h"

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
