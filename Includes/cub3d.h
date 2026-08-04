/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtodzzi <mtodzzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 11:57:16 by mtodzzi           #+#    #+#             */
/*   Updated: 2026/08/04 00:00:00 by mtodzzi          ###   ########.fr       */
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

# define USAGE "Usage: ./cub3d <file.cub>\n"
# define CUB_CHARSET "01NSEW "

typedef struct s_texture
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
}	t_texture;

typedef struct s_data
{
	char		**map;
	int			map_height;
	int			map_width;
	int			player_x;
	int			player_y;
	int			player_count;
	t_texture	tex;
	int			floor_rgb[3];
	int			ceiling_rgb[3];
	int			floor_set;
	int			ceiling_set;
}	t_data;

/* init.c */
void	init_data(t_data *data);

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
int		texture_path(t_texture *tex, char *path);
int		valide_texture(t_texture *tex);

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

#endif
