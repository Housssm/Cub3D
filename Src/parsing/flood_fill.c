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
	copy = ft_calloc(total + 1, sizeof(char *));
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

static int	visit_cell(char **copy, t_point pt, t_stack *s)
{
	if (pt.y < 0 || pt.x < 0 || !copy[pt.y])
		return (s->leak = 1, 0);
	if (pt.x >= (int)ft_strlen(copy[pt.y]))
		return (s->leak = 1, 0);
	if (copy[pt.y][pt.x] == '1' || copy[pt.y][pt.x] == 'F')
		return (0);
	if (copy[pt.y][pt.x] == ' ')
		return (s->leak = 1, 0);
	copy[pt.y][pt.x] = 'F';
	return (1);
}

static int	push(t_stack *s, int y, int x)
{
	t_point	*bigger;

	if (s->top >= s->cap)
	{
		bigger = malloc(sizeof(t_point) * s->cap * 2);
		if (!bigger)
			return (0);
		ft_memcpy(bigger, s->pts, sizeof(t_point) * s->top);
		free(s->pts);
		s->pts = bigger;
		s->cap *= 2;
	}
	s->pts[s->top].y = y;
	s->pts[s->top].x = x;
	s->top++;
	return (1);
}

int	flood_fill(char **copy, int y, int x)
{
	t_stack	s;
	t_point	cur;

	s.cap = 64;
	s.top = 0;
	s.leak = 0;
	s.pts = malloc(sizeof(t_point) * s.cap);
	if (!s.pts)
		return (0);
	if (!push(&s, y, x))
		return (free(s.pts), 0);
	while (s.top > 0)
	{
		cur = s.pts[--s.top];
		if (!visit_cell(copy, cur, &s))
			continue ;
		if (!push(&s, cur.y + 1, cur.x) || !push(&s, cur.y - 1, cur.x)
			|| !push(&s, cur.y, cur.x + 1) || !push(&s, cur.y, cur.x - 1))
			return (free(s.pts), 0);
	}
	free(s.pts);
	return (!s.leak);
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
