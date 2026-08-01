#ifndef CUB3D_H
# define CUB3D_H

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
# define ESC 65307
# define RIGHT 100
# define LEFT 97
# define UP 119
# define DOWN 115
# define ARR_RIGHT 65363
# define ARR_LEFT 65361
# define MOUSE_SENS 0.001
# define PI 3.1415926535
# define NORTH 4.7123889
# define SOUTH 1.570796
# define EAST 0.0
# define WEST PI
# define SIDE_X 0
# define SIDE_Y 1
# define SIDE_X 0
# define SIDE_Y 1

typedef struct s_game	t_game;

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
}	t_minimap;

typedef struct s_texture
{
	char	*path;
	void	*img;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}	t_texture;

typedef struct s_raycast
{
	float	angle_cos;
	float	angle_sin;
	float	x_ray;
	float	y_ray;
	float	distance;
	float	height;
	int		beg_y;
	int		end;
	int		wall_orientation;
	int		side;
	float	wall_x;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	float	delta_dist_x;
	float	delta_dist_y;
	float	side_dist_x;
	float	side_dist_y;
	int		texture_x;
}	t_raycast;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	char		**map;
	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
	int			map_height;
	int			map_width;
	int			ceiling;
	int			floor;
	int			ceiling_is_set;
	int			floor_is_set;
	int			east_coast_text;
	int			west_coast_text;
	int			north_coast_text;
	int			south_coast_text;
	int			mouse_x;
	int			mouse_moving;
	int			mouse_hidden;
	t_texture	texture_north;
	t_texture	texture_south;
	t_texture	texture_west;
	t_texture	texture_east;
	t_player	player;
	t_minimap	minimap;
	t_raycast	raycast;
}	t_game;

int		game_initiation(t_game *game, char **av);
int		close_wind(t_game *game);
void	game_cleaning(t_game *game);
int		mouse_mvmt(int x, int y, t_game *game);
void	released_key(int keycode, t_player *player);
void	pressed_key(int keycode, t_game *game);
int		draw_loop(t_game *game);
void	player_mouvement(t_player *player);
void	ray_initiation(t_player *player, t_raycast *raycast, int col);
int		dda_application(t_game *game, t_raycast *raycast);
void	draw_empty_column(t_game *game, int x);
void	draw_column(t_game *game, int x, t_raycast *raycast);
void	draw_texture(t_game *game, t_raycast *raycast,
			t_texture *texture, int x);
void	minimap(t_game *game);
void	put_pixel(int x, int y, int color, t_game *game);
int		extract_scene(char **av, t_game *game);

#endif