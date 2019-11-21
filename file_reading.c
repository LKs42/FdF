/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reading.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <lugibone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 19:08:59 by lugibone          #+#    #+#             */
/*   Updated: 2019/11/21 15:52:16 by lugibone         ###   ########.fr       */
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
	free2d_array(curr_line);
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

t_point	**map_realloc(t_point **map, int y, t_scene *scene)
{
	t_point	**map2;
	size_t	s;

	s = sizeof(t_point*) * (y + 1);
	if (map2 = malloc(s) == NULL)
		file_error(scene, 0);
	ft_memcpy(map2, map, s - 1);
	free(map);
	return (map2);
}

void	file_error(t_scene *scene, int b)
{
	int i;

	i = -1;
	mlx_destroy_image(scene->mlx_ptr, scene->img_ptr);
	mlx_destroy_window(scene->mlx_ptr, scene->win_ptr);
	free(scene->point_a);
	free(scene->point_b);
	while (++i < scene->map_h)
		free(scene->map[i]);
	free(scene->map);
	free(scene);
	b ? usage() : 0;
	exit(0);
}

t_point	**fileread(int fd, t_scene *scene)
{
	char	**curr_line;
	char	*str;
	int		y;
	int		a;
	t_point **map;

	a = 0;
	if (map = (t_point**)malloc(sizeof(t_point*)) == NULL)
		file_error(scene, 0);
	y = 0;
	while (get_next_line(fd, &str) > 0)
	{
		if (check_line(str, scene) == 0)
			file_error(scene, 1);
		map = map_realloc(map, y, scene);
		curr_line = ft_split(str, " \n");
		a = 0;
		while (curr_line[a] != NULL)
			a++;
		if (map[y] = (t_point*)malloc(sizeof(t_point) * a) == NULL)
			file_error(scene, 0);
		loop(curr_line, map, y, scene);
		y++;
		free(str);
	}
	scene->map_h = y;
	return (map);
}
