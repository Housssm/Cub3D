/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtodzzi <mtodzzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 11:38:11 by mtodzzi           #+#    #+#             */
/*   Updated: 2026/08/04 00:00:00 by mtodzzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

char	**copy_map(char **map)
{
	char	**copy;
	int		total;
	int		i;

	total = count_map_lines(map);
	copy = malloc(sizeof(char *) * (total + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < total)
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
			return (free_line(copy), NULL);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static int	push_point(t_point **stack, int *cap, int *top, int y, int x)
{
	t_point	*bigger;

	if (*top >= *cap)
	{
		bigger = malloc(sizeof(t_point) * (*cap) * 2);
		if (!bigger)
			return (0);
		ft_memcpy(bigger, *stack, sizeof(t_point) * (*top));
		free(*stack);
		*stack = bigger;
		*cap = (*cap) * 2;
	}
	(*stack)[*top].y = y;
	(*stack)[*top].x = x;
	(*top)++;
	return (1);
}

static int	visit_point(char **copy, t_point pt, int *leak)
{
	if (pt.y < 0 || pt.x < 0 || !copy[pt.y])
	{
		*leak = 1;
		return (0);
	}
	if (pt.x >= (int)ft_strlen(copy[pt.y]))
	{
		*leak = 1;
		return (0);
	}
	if (copy[pt.y][pt.x] == '1' || copy[pt.y][pt.x] == 'F')
		return (0);
	if (copy[pt.y][pt.x] == ' ')
	{
		*leak = 1;
		return (0);
	}
	copy[pt.y][pt.x] = 'F';
	return (1);
}

static int	fill_loop(char **copy, t_point **stack, int *cap, int *top,
		int *leak)
{
	t_point	cur;

	while (*top > 0)
	{
		cur = (*stack)[--(*top)];
		if (!visit_point(copy, cur, leak))
			continue ;
		if (!push_point(stack, cap, top, cur.y + 1, cur.x)
			|| !push_point(stack, cap, top, cur.y - 1, cur.x)
			|| !push_point(stack, cap, top, cur.y, cur.x + 1)
			|| !push_point(stack, cap, top, cur.y, cur.x - 1))
			return (0);
	}
	return (1);
}

int	flood_fill(char **copy, int y, int x)
{
	t_point	*stack;
	int		cap;
	int		top;
	int		leak;

	cap = 64;
	stack = malloc(sizeof(t_point) * cap);
	if (!stack)
		return (0);
	top = 0;
	leak = 0;
	push_point(&stack, &cap, &top, y, x);
	if (!fill_loop(copy, &stack, &cap, &top, &leak))
		return (free(stack), 0);
	free(stack);
	return (!leak);
}

int	right_map(t_data *data, char **map)
{
	char	**copy;
	int		res;

	copy = copy_map(map);
	if (!copy)
		return (0);
	res = flood_fill(copy, data->player_y, data->player_x);
	free_line(copy);
	return (res);
}
