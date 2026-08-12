/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-har <hoel-har@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 11:57:16 by mtodzzi           #+#    #+#             */
/*   Updated: 2026/08/12 14:26:57 by hoel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include "mlx.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <math.h>
# include <stdbool.h>
# include "../Libft/libft/libft.h"
# include "../Libft/GNL/get_next_line.h"
# include "../minilibx-linux/mlx.h"

# define USAGE "Usage: ./cub3d <file.cub>\n"
# define CUB_CHARSET "01NSEW "
# define WIND_NAME "Cube"
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

typedef struct s_textr
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
}	t_textr;


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


typedef struct s_data
{
	char		**map;
	int			map_height;
	int			map_width;
	int			player_x;
	int			player_y;
	int			player_count;
	int			player_orientation;// rajoutee
	t_textr		tex;
	int			floor_rgb[3];
	int			ceiling_rgb[3];
	int			floor_set;
	int			ceiling_set;
}	t_data;

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
	// int			ceiling_is_set;
	// int			floor_is_set;
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

/* init.c */
void	init_data(t_data *data, t_game *game);

/* check_args.c */
int		is_cub_file(char *path);
int		is_xpm_file(char *path);
int		is_valide_file(char *path);

/* parsing_utils.c */
int		is_white_space(char c);
int		is_white_space_map(char c);
void	free_line(char **line);
int		is_empty_line(char *line);

/* check_texture.c */
char	*get_texture_path(char *path);
int		is_texture_id(char *path, int index);
int		texture_path(t_textr *tex, char *path);
int		valide_texture(t_textr *tex);

/* check_color.c */
int		is_valid_rgb(int *rgb);
int		is_color_id(char *path, int index);
char	**count_rgb(char *str);
int		check_tab_rgb(char **array);
int		floor_or_ceilling(t_data *data, char *line);

/* check_map.c */
int		find_player(t_data *data, int y, int x);
int		is_valid_char(t_data *data, char *line, int y);
int		is_valid_map(t_data *data, char **map);

/* map_closed.c */
int		count_map_lines(char **map);
int		check_walls(char *line);
int		is_close_map(char **map);

/* flood_fill.c */
char	**copy_map(char **map);
int		flood_fill(char **copy, int y, int x);
int		right_map(t_data *data, char **map);

/* extract_lines.c */
int		count_lines_arr(char **lines);
char	**read_all_lines(char *file);

/* build_map.c */
int		first_map_line(char **lines);
char	**build_map(char **lines, int start);
int		set_map_size(t_data *data);

/* parse_config.c */
int		get_line_type(char *line);
int		parse_config_line(t_data *data, char *line);
int		parse_all_config(t_data *data, char **lines, int end);
int		all_config_set(t_data *data);

/* parsing.c */
int		parse_scene(t_data *data, char *file);
void	free_data(t_data *data);

/* raycasting*/
int		game_initiation(t_game *game, t_data *data, char **av);
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
int		extract_scene(t_game *game, t_data *data);


#endif
