#ifndef CUB3D_H
#define CUB3D_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <sys/time.h>
# include <math.h>
# include "../Libft/libft/libft.h"
# include "../Libft/GNL/get_next_line.h"
# include "../minilibx-linux/mlx.h"


# define WIND_NAME "Cube"
# define USAGE "Usage: ./cub3d <file.cub>\n"
# define CLOSE_MOUSE 17
# define BITS_SIZE 32
# define DIM_X 750
# define DIM_Y 400
// # define MAX_WIDTH 1280
// # define MAX_HEIGHT 720
# define ESC 65307
# define RIGHT 100
# define LEFT 97
# define UP 119
# define DOWN 115
# define PI 3.1415926535
#define FOV 60 // filed of vue

// typedef struct s_data
// {
// 	char *wall; /// tempo
// 	int		cols;
// 	int		row;
// 	char *n_text;
// 	char *s_text;
// 	char *w_text;
// 	char *e_text;
// 	char *f_color;
// 	char *c_color;
// 	char **map;

// 	t_screen	*screen;
// }	t_data;
// typedef struct s_player
// {
// 	float	px;
// 	float	py;
// 	float	pdx;
// 	float	pdy;
// 	float	pa;

// }	t_player;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	void	*img;
	void	*wall;

	double	pos_x;
	double	pos_y;
	double	pos_dx;
	double	pos_dy;
	double	pa;

	int		tile_size;
	void	*player;
	void	*floor;
	int		w;
	int		h;
	int		nb_mouv;
	char 	**map;

	/*Dessiner la ligne pour raycasting*/
	int		line_lenght;
	int		endian;
	int		bits_per_piwel;

	// char    *north_texture;
    // char    *south_texture;
    // char    *east_texture;
    // char    *west_texture;
	// t_player	*player;
}	t_game;

typedef struct s_data
{
	char 	*wall; //tempo
	char 	*playa; //tempo
	char 	*floor; //tempo

    char    **map;
    char    *north_texture;
    char    *south_texture;
    char    *east_texture;
    char    *west_texture;
    char    *char_map;
    int     map_height;
    int     map_width;
    int     floor_color;
    int     ceilling_color;
    int     player;
    int     position_player_x;
    int     position_player_y;
    int     map_position;
	t_game	*game;
}   t_data;


void	find_pos(char **tab, double *x, double *y, double *direction);


//cleaning

int close_wind(t_data *data);
void	free_tab(char **tab);
int	delete_all_image(t_data *data);

//window creation
int	display(t_data *data);
int	wind_creation(t_data *data);

// raycast

void draw_line(t_game *game, int beginX, int beginY, int endX, int endY, int color);


#endif