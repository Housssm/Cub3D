#ifndef CUB3D_H
#define CUB3D_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <sys/time.h>
# include <math.h>
# include <stdbool.h>
# include "../Libft/libft/libft.h"
# include "../Libft/GNL/get_next_line.h"
# include "../minilibx-linux/mlx.h"


# define WIND_NAME "Cube"
# define USAGE "Usage: ./cub3d <file.cub>\n"
# define CLOSE_MOUSE 17
# define BITS_SIZE 64
# define MAX_WIDTH 1920
# define MAX_HEIGHT 1080
# define BLOCK  64
# define ESC 65307
# define RIGHT 100
# define LEFT 97
# define UP 119
# define DOWN 115
# define ARR_RIGHT 65363
# define ARR_LEFT 65361
# define PI 3.1415926535
// # define FOV 60 // filed of vue

typedef struct s_game t_game;


typedef struct s_player
{
	float	pos_x;
	float	pos_y;
	float	angle;
	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;
	bool	right_rotation;
	bool	left_rotation;
	
	t_game	*game;
}	t_player;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	void	*img;
	char 	**map;
	char	*data;
	int		bpp; //buffer
	int		size_line;
	int		endian;


	// char	*addr;
	// void	*wall;
	// void	*floor;
	// void	*player_img;
	// int		w;
	// int		h;
	int		map_height;
	int		map_width;

	// /*Dessiner la ligne pour raycasting*/
	// int		line_length;
	// int		bits_per_pixel;


	t_player	player;
}	t_game;


void	player_initialisation(t_player *player);
void put_pixel(int x, int y, int color, t_game *game);

int	file_to_img(t_game *game);


// typedef struct s_data
// {
// 	char 	*wall; //tempo
// 	char 	*playa; //tempo
// 	char 	*floor; //tempo

//     char    **map;
//     char    *north_texture;
//     char    *south_texture;
//     char    *east_texture;
//     char    *west_texture;
//     char    *char_map;
//     int     map_height;
//     int     map_width;
//     int     floor_color;
//     int     ceilling_color;
//     int     position_player_x;
//     int     position_player_y;
//     int     map_position;
// 	t_game	*game;
// 	t_player *player;
// }   t_data;


#endif