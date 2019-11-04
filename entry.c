/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 15:49:46 by lugibone          #+#    #+#             */
/*   Updated: 2019/11/04 18:32:44 by lugibone         ###   ########.fr       */
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

void	loop(char **curr_line, t_point **map, int y, t_scene *scene)
{
	int x;
	int a = 0;
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

t_point	**fileread(int fd, t_scene *scene)
{
	char **curr_line;
	int	y;
	char *str;
	t_point **map;
	int a = 0;
	map = NULL;
	curr_line = NULL;
	str = malloc(sizeof(char) * 10000);	
	map = (t_point**)malloc(sizeof(t_point*) * 10000);	
	y = 0;
	while(get_next_line(fd, &str) > 0)
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

void fill_pixel(int *my_image_string, int x, int y, int color)
{
	int i;
	if (!(x <= 0 || y <= 0 || y >= HEIGHT || x >= WIDTH))
	{
		i = x + WIDTH * y;
		my_image_string[i] = color;
	}
}

t_point *ft_rot_x(t_point *point, t_scene *scene, t_point *new_point)
{
	float ag;
	t_point tmp;
	
	tmp.x = point->x;
	tmp.y = point->y;
	tmp.z = point->z;

	ag = scene->rot_x;

	new_point->x = tmp.x;
	new_point->y = tmp.y * cos(ag) - tmp.z * sin(ag);
	new_point->z = tmp.y * sin(ag) + tmp.z * cos(ag);
	return (new_point);
}


t_point *ft_rot_y(t_point *point, t_scene *scene, t_point *new_point)
{
	float ag;
	t_point tmp;
	
	tmp.x = point->x;
	tmp.y = point->y;
	tmp.z = point->z;

	ag = scene->rot_y;
	
	new_point->x = tmp.x * cos(ag) + tmp.z * sin(ag);
	new_point->y = tmp.y;
	new_point->z = -(tmp.x) * sin(ag) + tmp.z * cos(ag);

	return (new_point);
}


t_point *ft_rot_z(t_point *point, t_scene *scene, t_point *new_point)
{
	float ag;
	t_point tmp;
	
	tmp.x = point->x;
	tmp.y = point->y;
	tmp.z = point->z;

	ag = scene->rot_z;
	
	new_point->x = tmp.x * cos(ag) - tmp.y * sin(ag);
	new_point->y = tmp.x * sin(ag) + tmp.y * cos(ag);
	new_point->z = point->z;

	return (new_point);
}

void	ft_scale(t_point *point, float scale)
{
	point->x *= scale;
	point->y *= scale;
	point->z *= scale;
}

t_point	*ft_rot_matrix(t_point *point, t_scene *scene, t_point *new_point)
{
	float focale;
	float ag;

	ag = scene->rot_y;;
	focale = scene->focale;

	new_point->color = point->color;
	
	new_point->x = point->x - scene->map_w/2;
	new_point->y = point->y - scene->map_h/2;
	new_point->z = point->z;
	
	ft_rot_x(new_point, scene, new_point);
	ft_rot_y(new_point, scene, new_point);
	ft_rot_z(new_point, scene, new_point);
	
	new_point->x = new_point->x + scene->tr_x;
	new_point->y = new_point->y + scene->tr_y;
	new_point->z = new_point->z;
	
//	new_point->x = (focale * new_point->x)/point->z;
//	new_point->y = (focale * new_point->y)/point->z;

	ft_scale(new_point, scene->scale);
	return (new_point);
}

void liner(int *img, t_point *a, t_point *b)
{
	int x0 = a->x;
	int x1 = b->x;
	int y0 = a->y;
	int y1 = b->y;

	int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
	int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;
	int err = (dx>dy ? dx : -dy)/2, e2;

	while(!(x0==x1 && y0==y1))
	{
		fill_pixel(img, x0, y0, a->color);
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

void	map_iter(t_scene *scene,   void(*f)(t_point *, float), float a)
{
	int i;
	int j;

	i = -1;
	j = -1;
	while (++i < scene->map_h)
	{
		while(++j < scene->map_w)
		{
			f(&scene->map[i][j], a);
		}
		j = -1;
	}
}

int rgb_r(int color)
{
	return ((color & 0xFF0000) >> 16);
}

int rgb_g(int color)
{
	return((color & 0x00FF00) >> 8);
}

int rgb_b(int color)
{
	return ((color & 0x0000FF));
}

void	draw_hud(t_scene *scene)
{
	mlx_string_put(scene->mlx_ptr, scene->win_ptr, 50, 50, 0xFFFFFF, scene->title);
	mlx_string_put(scene->mlx_ptr, scene->win_ptr, 50, 70, 0xFFFFFF, ft_itoa_base(rgb_r(scene->bg_color), 10));
	mlx_string_put(scene->mlx_ptr, scene->win_ptr, 50, 90, 0xFFFFFF, ft_itoa_base(rgb_g(scene->bg_color), 10));
	mlx_string_put(scene->mlx_ptr, scene->win_ptr, 50, 110, 0xFFFFFF, ft_itoa_base(rgb_b(scene->bg_color), 10));
}

void	draw_scene(t_scene *scene)
{
	int i;
	int j;

	t_point *new_point;
	new_point = malloc(sizeof(t_point*));
	t_point *new_point2;
	new_point2 = malloc(sizeof(t_point*));

	i = -1;
	j = -1;
	while (++i < scene->map_h)
	{
		while(++j < scene->map_w - 1)
		{
			liner(scene->str, ft_rot_matrix(&scene->map[i][j], scene, new_point), ft_rot_matrix(&scene->map[i][j + 1], scene, new_point2));
		}
		j = -1;
	}
	i = -1;
	j = -1;
	while (++i < scene->map_h - 1)
	{
		while(++j < scene->map_w)
		{
			liner(scene->str, ft_rot_matrix(&scene->map[i][j], scene, new_point), ft_rot_matrix(&scene->map[i + 1][j], scene, new_point2));
		}
		j = -1;
	}
/*
	i = -1;
	j = -1;
	while (++i < scene->map_h - 1)
	{
		while(++j < scene->map_w - 1)
		{
			liner(scene->str, ft_rot_matrix(&scene->map[i][j + 1], scene, new_point), ft_rot_matrix(&scene->map[i + 1][j], scene, new_point2));
		}
		j = -1;
	}
	i = -1;
	j = -1;
	while (++i < scene->map_h - 1)
	{
		while(++j < scene->map_w - 1)
		{
			liner(scene->str, ft_rot_matrix(&scene->map[i][j], scene, new_point), ft_rot_matrix(&scene->map[i + 1][j + 1], scene, new_point2));
		}
		j = -1;
	}
*/
	free(new_point);
	free(new_point2);
}

void	show_map(t_scene *scene)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(i < scene->map_h)
	{
		while(j < scene->map_w)
		{
			ft_putnbr((int)&scene->map[i][j].z);
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
	scene->tr_x = 5;
	scene->tr_y = 5;
	scene->scale = 10;
	scene->img_ptr = mlx_new_image(scene->mlx_ptr, scene->win_width, scene->win_height);
	scene->str = (int*)mlx_get_data_addr(scene->img_ptr, &scene->bpp, &scene->sl, &scene->endian);
	scene->map = fileread(open(argv[1], O_RDONLY), scene);
	return (scene);
}

void	incrementy(t_point *point, float a)
{
	point->y += a;
}

void	incrementx(t_point *point, float a)
{
	point->x += a;
}

void	incrementz(t_point *point, float a)
{
	point->z += a;
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
	if (key == 0x74)
		scene->scale += 1;
	if (key == 0x79)
		scene->scale -= 1;
	if (key == 0)
		scene->bg_color -= 0x010000;
	if (key == 1)
		scene->bg_color -= 0x000100;
	if (key == 2)
		scene->bg_color -= 0x000001;
	if (key == 6)
		scene->bg_color += 0x010000;
	if (key == 7)
		scene->bg_color += 0x000100;
	if (key == 8)
		scene->bg_color += 0x000001;
	if (key == 122)
	{
		scene->rot_x = 0;
		scene->rot_y = 0;
		scene->rot_z = 0;
	}
	if (key == 120)
	{
		scene->rot_x = 0.954;
	//		scene->rot_y = 0.785398;
		scene->rot_z = 0.785398;
	}
	fill_img(scene, scene->bg_color);
	if (key == 0x7B)
		scene->tr_x -= 0.5;
	if (key == 0x7C)
		scene->tr_x += 0.5;
	if (key == 0x7D)
		scene->tr_y += 0.5;
	if (key == 0x7E)
		scene->tr_y -= 0.5;
	draw_scene(scene);
	mlx_put_image_to_window(scene->mlx_ptr, scene->win_ptr, scene->img_ptr, 0, 0);
	draw_hud(scene);	
return (0);
}

int	check_extension(char *str, char *extension)
{
	return (ft_strcmp(str + ft_strlen(str) - ft_strlen(extension), extension) == 0) ? 0 : 1;
}

int	main(int argc, char **argv)
{
	t_scene *scene;


	scene = NULL;
	if (argc == 2 && (!(check_extension(argv[1], ".fdf"))))
		scene = init_scene(WIDTH, HEIGHT, argv[1], argv);
	else
		return (0);
	fill_img(scene, scene->bg_color);
	//show_map(scene);
	draw_scene(scene);
	mlx_put_image_to_window(scene->mlx_ptr, scene->win_ptr, scene->img_ptr, 0, 0);
	mlx_key_hook(scene->win_ptr, deal_key, scene);
	draw_hud(scene);
	mlx_loop(scene->mlx_ptr);
	return (0);
}
