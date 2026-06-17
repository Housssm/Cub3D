#ifndef CUB3D_H
#define CUB3D_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <sys/time.h>
# include "Libft/libft/libft.h"
# include "Libft/GNL/get_next_line.h"
# include "minilibx-linux/mlx.h"


# define WIND_NAME "Cube"
# define BITS_SIZE 32
# define CLOSE_MOUSE 17
# define USAGE "Usage: ./cub3d <file.cub>\n"

typedef struct s_data
{
	char *wall; /// tempo
	int		cols;
	int		row;
	char *n_text;
	char *s_text;
	char *w_text;
	char *e_text;
	char *f_color;
	char *c_color;
	char **map;

	void	*mlx;
	void	*win;
	void	*img;

}	t_data;


//cleaning

int	close_wind(t_data *data);


#endif