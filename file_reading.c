/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reading.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 19:08:59 by lugibone          #+#    #+#             */
/*   Updated: 2019/11/05 19:12:05 by lugibone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	loop(char **curr_line, t_point **map, int y, t_scene *scene)
{
	int x;
	int a;

	a = 0;
	x = 0;
	while (curr_line[a] != NULL)
		a++;
	while (x < a)
	{
		map[y][x].x = (float)x;
		map[y][x].y = (float)y;
		map[y][x].z = (float)ft_atoi(curr_line[x]);
		map[y][x].color = 0x22B41F;
		x++;
	}
	scene->map_w = x;
}

void	show_map(t_scene *scene)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < scene->map_h)
	{
		while (j < scene->map_w)
		{
			ft_putnbr((int)scene->map[i][j].z);
			ft_putchar(' ');
			j++;
		}
		ft_putchar('\n');
		j = 0;
		i++;
	}
}

t_point	**fileread(int fd, t_scene *scene)
{
	char **curr_line;
	int	y;
	char *str;
	t_point **map;
	int a;

	a = 0;
	map = NULL;
	curr_line = NULL;
	str = malloc(sizeof(char) * 10000);
	map = (t_point**)malloc(sizeof(t_point*) * 10000);
	y = 0;
	while (get_next_line(fd, &str) > 0)
	{
		curr_line = ft_split(str, " \n");
		a = 0;
		while (curr_line[a] != NULL)
			a++;
		map[y] = (t_point*)malloc(sizeof(t_point) * a);
		loop(curr_line, map, y, scene);
		y++;
	}
	scene->map_h = y;
	map[y] = NULL;
	free(str);
	return (map);
}
