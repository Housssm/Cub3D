#ifndef CUB3D_H
#define CUB3D_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <sys/time.h>
# include "../Libft/libft/libft.h"
# include "../Libft/GNL/get_next_line.h"
# include "../minilibx-linux/mlx.h"


# define WIND_NAME "Cube"
# define USAGE "Usage: ./cub3d <file.cub>\n"
# define CLOSE_MOUSE 17
# define BITS_SIZE 32
# define DIM_X 750
# define DIM_Y 400
// # define IMG_WALL "Images/wall_bank.xpm"
// # define IMG_FLOOR "Images/floor_bank.xpm"
// # define IMG_COLL "Images/money.xpm"
// # define IMG_PLAYER "Images/Robber_beg.xpm"
// # define IMG_PLAYER2 "Images/Robber_med.xpm"
// # define IMG_PLAYER3 "Images/Robber_end.xpm"
// # define IMG_EXIT "Images/exit.xpm"
// # define IMG_DANG "Images/police.xpm"
// # define MAX_WIDTH 1280
// # define MAX_HEIGHT 720
# define ESC 65307
# define RIGHT 100
# define LEFT 97
# define UP 119
# define DOWN 115

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


typedef struct s_game
{
	void	*mlx;
	void	*win;
	void	*img;
	void	*wall;

	// void	*colectible;
	int		pos_x;
	int		pos_y;
	int		pos_ex_x;
	int		pos_ex_y;
	int		tile_size;
	void	*player;

	// void	*exit;
	void	*floor;
	// void	*danger;
	int		w;
	int		h;
	int		nb_mouv;
	// char    *north_texture;
    // char    *south_texture;
    // char    *east_texture;
    // char    *west_texture;
	char 	**map;
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


void	find_pos(char **tab, int *x, int *y);


//cleaning

int close_wind(t_data *data);
void	free_tab(char **tab);
int	delete_all_image(t_data *data);

//window
int	display(t_data *data);


#endif