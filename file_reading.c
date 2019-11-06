/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reading.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 19:08:59 by lugibone          #+#    #+#             */
/*   Updated: 2019/11/06 19:21:19 by lugibone         ###   ########.fr       */
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

t_point	**map_realloc(t_point **map, int y)
{
	t_point **map2;
//fuite de mémoire ici car tu free pas toutes les dimensions des maps enfin je suppose vu que ta pas tester
	map2 = NULL;
	map2 = malloc(sizeof(t_point*) * (y + 1));
	ft_memcpy(map2, map, sizeof(t_point*) * (y + 1));
	free(map);
	map = malloc(sizeof(t_point*) * (y + 1));
	ft_memcpy(map, map2, sizeof(t_point*) * (y + 1));
	free(map2);
	return (map);
}

void	file_error(t_scene *scene)
{
	int i;
	int j;

	i = -1;
	j = -1;
	ft_putendl("usage: ./fdf map_path");
	free(scene->point_a);
	free(scene->point_b);
	free(scene->mlx_ptr);
	free(scene->win_ptr);
	free(scene->img_ptr);
	free(scene->str);
	while (++i < scene->map_h)
		free(scene->map[i]);
	free(scene->map);
	free(scene);
	while(1);
	exit(0);
}

void	free2d_array(char **str)
{
	int i;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
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
	map = (t_point**)ft_memalloc(sizeof(t_point*));
	y = 0;
	while (get_next_line(fd, &str) > 0)
	{
		if (check_line(str, scene) == 0)
			file_error(scene);
		map = map_realloc(map, y);
		curr_line = ft_split(str, " \n");
		a = 0;
		while (curr_line[a] != NULL)
			a++;
		map[y] = (t_point*)ft_memalloc(sizeof(t_point) * a);
		loop(curr_line, map, y, scene);
		y++;
		free(str);
	}
	free2d_array(curr_line);
	scene->map_h = y;
	map[y] = NULL;
	return (map);
}
