/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 15:49:46 by lugibone          #+#    #+#             */
/*   Updated: 2019/10/29 17:51:58 by lugibone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <math.h>
#include "libft.h"
#include "mlx.h"
#include <fcntl.h>
#define WIDTH 2000
#define HEIGHT 2000
#define TITLE "hell world"
#define ABS(N) ((N<0)?(-N):(N))

void	loop(char **curr_line, t_point ***map, int y, t_scene *scene)
{
	int x;
	int a = 0;
	t_point tmp;
	x = 0;
	while (curr_line[a] != NULL)
		a++;
	while (x < a)
	{
		map[y][x] = malloc(sizeof(t_point*));
		map[y][x]->x = (float)x;
		map[y][x]->y = (float)y;
		map[y][x]->z = (float)ft_atoi(curr_line[x]);
		x++;
	}
	scene->map_w = x;
	map[y][x] = NULL;
}
	
t_point	***fileread(int fd, t_scene *scene)
{
	char **curr_line;
	int	y;
	char *str;
	t_point ***map;
	int a = 0;
	map = NULL;
	curr_line = NULL;
	str = malloc(sizeof(char) * 10000);	
	map = malloc(sizeof(t_point***) * 10000);	
	y = 0;
	while(get_next_line(fd, &str) > 0)
	{
		curr_line = ft_split(str, " \n");
		a = 0;
		while (curr_line[a] != NULL)
			a++;
		map[y] = malloc(sizeof(t_point**) * a);
		loop(curr_line, map, y, scene);
		y++;
	}
	scene->map_h = y;
	map[y] = NULL;
	return (map);
}

void fill_pixel(int *my_image_string, int x, int y, int color)
{
	int i;

	i = x + WIDTH*y;
	my_image_string[i] = color;
}

t_point *ft_rot_x(t_point *point, t_scene *scene, t_point *new_point)
{
	float ag;

	ag = scene->rot_x;

	new_point->x = point->x + 5;
	new_point->y = point->y * cos(ag) - point->z * sin(ag);
	new_point->z = point->y * sin(ag) + point->z * cos(ag);
	return (new_point);
}


t_point *ft_rot_y(t_point *point, t_scene *scene, t_point *new_point)
{
	float ag;

	ag = scene->rot_y;

	new_point->x = point->x * cos(ag) + point->z * sin(ag);
	new_point->y = point->y;
	new_point->z = -(point->x) * sin(ag) + point->z * cos(ag);

	return (new_point);
}


t_point *ft_rot_z(t_point *point, t_scene *scene, t_point *new_point)
{
	float ag;

	ag = scene->rot_z;

	new_point->x = point->x * cos(ag) - point->y * sin(ag);
	new_point->y = point->x * sin(ag) + point->y * cos(ag);
	new_point->z = point->z;

	return (new_point);
}

void	ft_scale(t_point *point, float scale)
{
	point->x *= scale;
	point->y *= scale;
	point->z *= scale;
}

t_point	*ft_rot_matrix(t_point *point, t_scene *scene)
{
	float focale;
	t_point *new_point;
	float ag;

	ag = scene->rot_y;;
	new_point = malloc(sizeof(t_point) * 5);
	focale = scene->focale;

	ft_rot_x(point, scene, new_point);
	ft_rot_y(new_point, scene, new_point);
	ft_rot_z(new_point, scene, new_point);
	
	ft_scale(new_point, scene->scale);

//	new_point->x = (focale * new_point->x)/point->z;
//	new_point->y = (focale * new_point->y)/point->z;
	return (new_point);
}


void liner(int *img, t_point *a, t_point *b, int color) {
	int x0 = a->x;
	int x1 = b->x;
	int y0 = a->y;
	int y1 = b->y;

	int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
	int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;
	int err = (dx>dy ? dx : -dy)/2, e2;

	while(!(x0==x1 && y0==y1))
	{
		fill_pixel(img, x0, y0, color);
		e2 = err;
		if (e2 >-dx) { err -= dy; x0 += sx; }
		if (e2 < dy) { err += dx; y0 += sy; }
	}
}

void    fill_img(t_scene *param, int color)
{
        int i;
        int c;

        c = color;
        i = 0;
        while(i < param->win_width * param->win_height)
        {
                param->str[i] = c;
                i++;
        }
}

void	draw_scene(t_scene *scene)
{
	int i;
	int j;

	i = -1;
	j = -1;
	while (++i < scene->map_h)
	{
		while(++j < scene->map_w - 1)
		{
			liner(scene->str, ft_rot_matrix(scene->map[i][j], scene), ft_rot_matrix(scene->map[i][j + 1], scene), 0xFFFFFF);
		}
		j = -1;
	}
i = -1;
j = -1;
	while (++i < scene->map_h - 1)
	{
		while(++j < scene->map_w)
		{
			liner(scene->str, ft_rot_matrix(scene->map[i][j], scene), ft_rot_matrix(scene->map[i + 1][j], scene), 0x00FF00);
		}
		j = -1;
	}
}

void	show_map(t_scene *scene)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	while(scene->map[i])
	{
		while(scene->map[i][j])
		{
			ft_putnbr(scene->map[i][j]->z);
			ft_putchar(' ');
			j++;
		}
	ft_putchar('\n');
	j = 0;
	i++;
	}
}

t_scene *init_scene(int w, int h, char *str, char **argv)
{
        t_scene *scene;

        scene = malloc(sizeof(t_scene));
	scene->bg_color = 0x32644B;
	scene->bg_color = 0x181818;
        scene->win_height = h;
        scene->win_width = w;
        scene->map_h = 0;
        scene->map_w = 0;
        scene->mlx_ptr = mlx_init();
        scene->title = str;
        scene->win_ptr = mlx_new_window(scene->mlx_ptr, w, h, str);
        scene->focale = 100;
        scene->rot_x = 0;
        scene->rot_y = 0;
        scene->rot_z = 0;
        scene->scale = 100;
	scene->img_ptr = mlx_new_image(scene->mlx_ptr, scene->win_width, scene->win_height);
        scene->str = (int*)mlx_get_data_addr(scene->img_ptr, &scene->bpp, &scene->sl, &scene->endian);
	scene->map = fileread(open(argv[1], O_RDONLY), scene);
	return (scene);
}

int	deal_key(int key, t_scene *scene)
{
	ft_putnbr(key);
	ft_putchar('\n');
	if (key == 49)
		exit(0);
	if (key == 12)
		scene->rot_x += 0.04;
	if (key == 13)
		scene->rot_x -= 0.04;
	if (key == 14)
		scene->rot_x = 0;
	if (key == 15)
		scene->rot_y += 0.04;
	if (key == 16)
		scene->rot_y -= 0.04;
	if (key == 17)
		scene->rot_y = 0;
	if (key == 32)
		scene->rot_z += 0.04;
	if (key == 34)
		scene->rot_z -= 0.04;
	if (key == 31)
		scene->rot_z = 0;
	if (key == 125)
		scene->scale += 1;
	if (key == 126)
		scene->scale -= 1;
	if (key == 0)
		scene->bg_color -= 0xFF0000;
	if (key == 1)
		scene->bg_color -= 0x00FF00;
	if (key == 2)
		scene->bg_color -= 0x0000FF;
	if (key == 6)
		scene->bg_color += 0xFF0000;
	if (key == 7)
		scene->bg_color += 0x00FF00;
	if (key == 8)
		scene->bg_color += 0x0000FF;
	fill_img(scene, scene->bg_color);
	draw_scene(scene);
	mlx_put_image_to_window(scene->mlx_ptr, scene->win_ptr, scene->img_ptr, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_scene *scene;

	scene = NULL;
	if (argc == 2)
		scene = init_scene(WIDTH, HEIGHT, TITLE, argv);
	fill_img(scene, scene->bg_color);
	show_map(scene);
	draw_scene(scene);
	mlx_put_image_to_window(scene->mlx_ptr, scene->win_ptr, scene->img_ptr, 0, 0);
 	mlx_key_hook(scene->win_ptr, deal_key, scene);
	mlx_loop(scene->mlx_ptr);
	return (0);
}
