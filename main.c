/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-har <hoel-har@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 14:35:31 by hoel-har          #+#    #+#             */
/*   Updated: 2026/06/17 19:47:16 by hoel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"




void	remove_newline(char **tab)
{
	int	i;
	int	j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (tab[i][j] == '\n')
				tab[i][j] = '\0';
			j++;
		}
		i++;
	}
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	size_fd(int fd)
{
	int		i;
	char	*str;

	i = 0;
	while (1)
	{
		str = get_next_line(fd);
		if (str == NULL)
			break ;
		i += 1;
		free(str);
	}
	close (fd);
	return (i);
}

char	**extract_map(char **av)
{
	int				fd;
	int				j;
	int				len_fd;
	char			**tab;

	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Check Rights\n", 1), NULL);
	len_fd = size_fd(fd);
	fd = open(av[1], O_RDONLY);
	j = 0;
	tab = malloc(sizeof(char *) * (len_fd + 1));
	if (!tab)
		return (free_tab(tab), NULL);
	while (1)
	{
		tab[j] = get_next_line(fd);
		if (tab[j] == NULL)
			break ;
		j++;
	}
	close(fd);
	tab[j] = NULL;
	remove_newline(tab);
	return (tab);
}
void	fill_data(t_data *data, char **av)
{
	data->wall = "images/wall.xpm"; /// tempo
	data->cols = 39;
	data->row = 6;
	data->n_text = NULL;
	data->s_text = NULL;
	data->w_text = NULL;
	data->e_text = NULL;
	data->f_color = "images/floor.xpm";
	data->c_color = NULL;
	data->map = extract_map(av);

	// data->mlx;
	// data->win;
	// data->img;
}

int	wind_creation(t_data *data)
{
	int	width;
	int	height;

	width = data->cols * BITS_SIZE;
	height = data->row * BITS_SIZE;
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		ft_putstr_fd("ERROR:Mlx init failed\n", 2);
		exit(1);
	}
	data->win = mlx_new_window(data->mlx, width, height, WIND_NAME);
	if (!data->win)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		return (1);
	}
	return (0);
}
int	display(t_data *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (file_to_img(data))
		return (close_wind(all), 1);
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (fill_display(data, i, j))
				return (close_wind(data), 1);
			j++;
		}
		i++;
	}
	display_mouv(all);
	return (0);
}

int main(int ac, char **av)
{
	t_data	data;
	
	(void)ac;
	fill_data(&data, av);
	if (wind_creation(&data))
		return (1);//FREE
	if (display(&data))
		RETURN (1); //FREE
	// mlx_hook((&data)->win, CLOSE_MOUSE, 0, close_wind, &data);
	mlx_loop(data.mlx);
		
	

	return (0);
}