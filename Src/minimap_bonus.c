#include "../Include/cub3d.h"

void	draw_block(t_game *game, int xy[2], int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel(xy[0] + i, xy[1] + j, color, game);
			j++;
		}
		i++;
	}
}

void	draw_map(t_game *game)
{
	int	i;
	int	j;
	int	xy[2];

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == '1')
			{
				xy[0] = game->minimap.offset_x + j * game->minimap.block_size;
				xy[1] = game->minimap.offset_y + i * game->minimap.block_size;
				draw_block(game, xy, game->minimap.block_size, 0xFFC0CB);
			}
			j++;
		}
		i++;
	}
}

void	draw_player(t_game *game)
{
	int	xy[2];
	int	size;

	size = 4;
	xy[0] = game->minimap.offset_x + (int)(game->player.pos_x / BLOCK)
		* game->minimap.block_size - size / 2;
	xy[1] = game->minimap.offset_y + (int)(game->player.pos_y / BLOCK)
		* game->minimap.block_size - size / 2;
	draw_block(game, xy, size, 0x00FF00);
}

void	minimap(t_game *game)
{
	draw_map(game);
	draw_player(game);
}
