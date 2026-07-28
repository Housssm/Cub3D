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
# define NORTH 0.0
# define SOUTH PI
# define EAST (PI /2)
# define WEST (3 * PI / 2)

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

typedef struct s_minimap
{
	int	offset_x;
	int	offset_y;
	int	block_size;
} t_minimap;

typedef	struct s_raycast
{
	float	angle_cos;
	float	angle_sin;
	float	x_ray;
	float	y_ray;
	float	dist;
	float	height;
	int		beg_y;
	int		end;
} t_raycast;


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
	int		map_height;
	int		map_width;
	int		ceiling;
	int		floor;

	int		east_cost;
	int		west_cost;
	int		north_cost;
	int		south_cost;

	t_player	player;
	t_minimap	minimap;
	t_raycast	raycast;
}	t_game;

void	player_initialisation(t_player *player);
void put_pixel(int x, int y, int color, t_game *game);

int	file_to_img(t_game *game);


//BONUS

void	minimap(t_game *game);



#endif