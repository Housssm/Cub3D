#include "../Includes/cub3d.h"

static int	scene_error(char *message)
{
	ft_putstr_fd("Error\n", 2);
	ft_putendl_fd(message, 2);
	return (1);
}

static void	remove_newline(char **tab)
{
	int		i;
	size_t	len;

	i = 0;
	while (tab[i])
	{
		len = ft_strlen(tab[i]);
		while (len > 0 && (tab[i][len - 1] == '\n'
			|| tab[i][len - 1] == '\r'))
		{
			tab[i][len - 1] = '\0';
			len--;
		}
		i++;
	}
}

static int	size_fd(int fd)
{
	int		i;
	char	*str;

	i = 0;
	while (1)
	{
		str = get_next_line(fd);
		if (str == NULL)
			break ;
		i++;
		free(str);
	}
	close(fd);
	return (i);
}

static char	**read_data(char *filename)
{
	int		fd;
	int		line_count;
	int		i;
	char	**lines;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	line_count = size_fd(fd);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	lines = malloc(sizeof(char *) * (line_count + 1));
	if (!lines)
		return (close(fd), NULL);
	i = 0;
	while (i < line_count)
	{
		lines[i] = get_next_line(fd);
		if (!lines[i])
			break ;
		i++;
	}
	lines[i] = NULL;
	close(fd);
	remove_newline(lines);
	return (lines);
}

static char	*skip_spaces(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (line);
}

static int	is_empty_line(char *line)
{
	line = skip_spaces(line);
	return (*line == '\0');
}

static int	is_map_line(char *line)
{
	int	i;
	int	content;

	i = 0;
	content = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '0' && line[i] != '1'
			&& line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W')
			return (0);
		if (line[i] != ' ')
			content = 1;
		i++;
	}
	return (content);
}

static char	*copy_path(char *line)
{
	char	*path;

	line = skip_spaces(line);
	if (*line == '\0')
		return (NULL);
	path = ft_strtrim(line, " \t");
	if (!path || path[0] == '\0')
	{
		free(path);
		return (NULL);
	}
	return (path);
}

static int	set_texture(char *line, t_texture *texture)
{
	if (texture->path)
		return (scene_error("Duplicate texture identifier"));
	texture->path = copy_path(line);
	if (!texture->path)
		return (scene_error("Missing texture path"));
	return (0);
}

static int	parse_number(char **line, int *number)
{
	int	value;

	*line = skip_spaces(*line);
	if (!ft_isdigit(**line))
		return (1);
	value = 0;
	while (ft_isdigit(**line))
	{
		value = value * 10 + (**line - '0');
		if (value > 255)
			return (1);
		(*line)++;
	}
	*line = skip_spaces(*line);
	*number = value;
	return (0);
}

static int	parse_color(char *line, int *color, int *is_set)
{
	int	r;
	int	g;
	int	b;

	if (*is_set)
		return (scene_error("Duplicate floor or ceiling color"));
	if (parse_number(&line, &r) || *line++ != ',')
		return (scene_error("Invalid RGB color"));
	if (parse_number(&line, &g) || *line++ != ',')
		return (scene_error("Invalid RGB color"));
	if (parse_number(&line, &b))
		return (scene_error("Invalid RGB color"));
	line = skip_spaces(line);
	if (*line != '\0')
		return (scene_error("Unexpected content after RGB color"));
	*color = (r << 16) | (g << 8) | b;
	*is_set = 1;
	return (0);
}

static int	parse_config_line(t_game *game, char *line)
{
	line = skip_spaces(line);
	if (!ft_strncmp(line, "NO", 2) && (line[2] == ' ' || line[2] == '\t'))
		return (set_texture(line + 2, &game->texture_north));
	if (!ft_strncmp(line, "SO", 2) && (line[2] == ' ' || line[2] == '\t'))
		return (set_texture(line + 2, &game->texture_south));
	if (!ft_strncmp(line, "WE", 2) && (line[2] == ' ' || line[2] == '\t'))
		return (set_texture(line + 2, &game->texture_west));
	if (!ft_strncmp(line, "EA", 2) && (line[2] == ' ' || line[2] == '\t'))
		return (set_texture(line + 2, &game->texture_east));
	if (line[0] == 'F' && (line[1] == ' ' || line[1] == '\t'))
		return (parse_color(line + 1, &game->floor, &game->floor_is_set));
	if (line[0] == 'C' && (line[1] == ' ' || line[1] == '\t'))
		return (parse_color(line + 1, &game->ceiling,
				&game->ceiling_is_set));
	return (scene_error("Unknown scene identifier"));
}

static int	config_is_complete(t_game *game)
{
	if (!game->texture_north.path || !game->texture_south.path
		|| !game->texture_east.path || !game->texture_west.path)
		return (scene_error("Four wall textures are required"));
	if (!game->floor_is_set || !game->ceiling_is_set)
		return (scene_error("Floor and ceiling colors are required"));
	return (0);
}

static int	copy_map(t_game *game, char **lines, int start)
{
	int	count;
	int	i;
	int	width;

	count = 0;
	while (lines[start + count])
	{
		if (is_empty_line(lines[start + count])
			|| !is_map_line(lines[start + count]))
			return (scene_error("Invalid line inside map"));
		count++;
	}
	if (count == 0)
		return (scene_error("Missing map"));
	game->map = malloc(sizeof(char *) * (count + 1));
	if (!game->map)
		return (scene_error("Memory allocation failed"));
	i = 0;
	width = 0;
	while (i < count)
	{
		game->map[i] = ft_strdup(lines[start + i]);
		if (!game->map[i])
		{
			game->map[i] = NULL;
			return (scene_error("Memory allocation failed"));
		}
		if ((int)ft_strlen(game->map[i]) > width)
			width = ft_strlen(game->map[i]);
		i++;
	}
	game->map[i] = NULL;
	game->map_height = count;
	game->map_width = width;
	return (0);
}

void	init_direction(t_player *player, char c)
{
	if (c == 'N')
		player->angle = NORTH;
	if (c == 'S')
		player->angle = SOUTH;
	if (c == 'E')
		player->angle = EAST;
	if (c == 'W')
		player->angle = WEST;
}

int	find_pos(t_game *game)
{
	int	i;
	int	j;
	int	players;

	i = 0;
	players = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (ft_strchr("NSEW", game->map[i][j]))
			{
				game->player.pos_x = j * BITS_SIZE + BITS_SIZE / 2;
				game->player.pos_y = i * BITS_SIZE + BITS_SIZE / 2;
				init_direction(&game->player, game->map[i][j]);
				game->map[i][j] = '0';
				players++;
			}
			j++;
		}
		i++;
	}
	if (players != 1)
		return (scene_error("Map must contain exactly one player"));
	return (0);
}

static char	map_value(t_game *game, int x, int y)
{
	if (y < 0 || y >= game->map_height || x < 0)
		return (' ');
	if (x >= (int)ft_strlen(game->map[y]))
		return (' ');
	return (game->map[y][x]);
}

static int	validate_closed_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == '0'
				&& (map_value(game, x - 1, y) == ' '
					|| map_value(game, x + 1, y) == ' '
					|| map_value(game, x, y - 1) == ' '
					|| map_value(game, x, y + 1) == ' '))
				return (scene_error("Map is not closed by walls"));
			x++;
		}
		y++;
	}
	return (0);
}

static int	has_cub_extension(char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 5)
		return (0);
	return (!ft_strncmp(filename + len - 4, ".cub", 4));
}

int	extract_scene(char **av, t_game *game)
{
	char	**lines;
	int		i;
	int		map_start;

	if (!has_cub_extension(av[1]))
		return (scene_error("Scene file must end with .cub"));
	lines = read_data(av[1]);
	if (!lines)
		return (scene_error("Cannot open scene file"));
	i = 0;
	map_start = -1;
	while (lines[i])
	{
		if (is_empty_line(lines[i]))
			i++;
		else if (is_map_line(lines[i]))
		{
			map_start = i;
			break ;
		}
		else if (parse_config_line(game, lines[i]))
			return (free_split(lines), 1);
		else
			i++;
	}
	if (config_is_complete(game))
		return (free_split(lines), 1);
	if (map_start < 0 || copy_map(game, lines, map_start))
		return (free_split(lines), 1);
	free_split(lines);
	if (find_pos(game) || validate_closed_map(game))
		return (1);
	return (0);
}

int	extract_scene(t_game *game, t_data *data)
{
	data->map;
	data->map_height;
	data->map_width;
	data->player_x;
	data->player_y;
	data->tex;
	data->floor_rgb;
	data->ceiling_rgb;
	
	return (0);
}