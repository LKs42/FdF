/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 15:49:46 by lugibone          #+#    #+#             */
/*   Updated: 2019/11/05 17:27:38 by lugibone         ###   ########.fr       */
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
	ft_scale(new_point, scene->scale);
	return (new_point);
}

void liner(int *img, t_point *a, t_point *b)
{
	int tab[10];

	tab[0] = a->x;
	tab[1] = b->x;
	tab[2] = a->y;
	tab[3] = b->y;
	tab[4] = abs(tab[1]-tab[0]);
	tab[5] = tab[0]<tab[1] ? 1 : -1;
	tab[6] = abs(tab[3]-tab[2]);
	tab[7] = tab[2]<tab[3] ? 1 : -1;
	tab[8] = (tab[4]>tab[6] ? tab[4] : -tab[6])/2;
	while(!(tab[0]==tab[1] && tab[2]==tab[3]))
	{
		fill_pixel(img, tab[0], tab[2], a->color);
		tab[9] = tab[8];
		if (tab[9] > -tab[4])
		{
			tab[8] -= tab[6];
			tab[0] += tab[5];
		}
		if (tab[9] < tab[6])
		{
			tab[8] += tab[4];
			tab[2] += tab[7];
		}
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
			f(&scene->map[i][j], a);
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

void	state_hud(t_scene *scene)
{
	if (scene->state == TRANSLATE)
		mlx_string_put(scene->mlx_ptr, scene->win_ptr, 30, 130, 0xFFFFFF, "TRANSLATION");
	if (scene->state == ROTATE)
		mlx_string_put(scene->mlx_ptr, scene->win_ptr, 30, 130, 0xFFFFFF, "ROTATION");
	if (scene->state == SCALE)
		mlx_string_put(scene->mlx_ptr, scene->win_ptr, 30, 130, 0xFFFFFF, "SCALING");
}

void	draw_hud(t_scene *scene)
{
	mlx_string_put(scene->mlx_ptr, scene->win_ptr, 30, 50, 0xFFFFFF, scene->title);
	mlx_string_put(scene->mlx_ptr, scene->win_ptr, 30, 70, 0xFFFFFF, "R: ");
	mlx_string_put(scene->mlx_ptr, scene->win_ptr, 30, 90, 0xFFFFFF, "G: ");
	mlx_string_put(scene->mlx_ptr, scene->win_ptr, 30, 110, 0xFFFFFF, "B: ");
	mlx_string_put(scene->mlx_ptr, scene->win_ptr, 50, 70, 0xFFFFFF, ft_itoa_base(rgb_r(scene->bg_color), 10));
	mlx_string_put(scene->mlx_ptr, scene->win_ptr, 50, 90, 0xFFFFFF, ft_itoa_base(rgb_g(scene->bg_color), 10));
	mlx_string_put(scene->mlx_ptr, scene->win_ptr, 50, 110, 0xFFFFFF, ft_itoa_base(rgb_b(scene->bg_color), 10));
	state_hud(scene);
}

void	draw_scene(t_scene *scene)
{
	int i;
	int j;
	t_point *new_point;
	t_point *new_point2;
	
	new_point = malloc(sizeof(t_point*));
	new_point2 = malloc(sizeof(t_point*));

	i = -1;
	j = -1;
	while (++i < scene->map_h)
	{
		while(++j < scene->map_w - 1)
			liner(scene->str, ft_rot_matrix(&scene->map[i][j], scene, new_point), ft_rot_matrix(&scene->map[i][j + 1], scene, new_point2));
		j = -1;
	}
	i = -1;
	while (++i < scene->map_h - 1)
	{
		while(++j < scene->map_w)
			liner(scene->str, ft_rot_matrix(&scene->map[i][j], scene, new_point), ft_rot_matrix(&scene->map[i + 1][j], scene, new_point2));
		j = -1;
	}
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
			ft_putnbr((int)scene->map[i][j].z);
			ft_putchar(' ');
			j++;
		}
		ft_putchar('\n');
		j = 0;
		i++;
	}
}

void	set_scene(t_scene *scene)
{
	scene->bg_color = 0x181818;
	scene->map_h = 0;
	scene->map_w = 0;
	scene->focale = 100;
	scene->rot_x = 0;
	scene->rot_y = 0;
	scene->rot_z = 0;
	scene->tr_x = 5;
	scene->tr_y = 5;
	scene->scale = 10;
}

t_scene *init_scene(int w, int h, char *str, char **argv)
{
	t_scene *scene;

	scene = malloc(sizeof(t_scene));
	set_scene(scene);
	scene->win_height = h;
	scene->win_width = w;
	scene->mlx_ptr = mlx_init();
	scene->title = str;
	scene->win_ptr = mlx_new_window(scene->mlx_ptr, w, h, str);
	scene->state = TRANSLATE;
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

void	change_color(t_point *point, float a)
{
	(void)a;
	point->color = point->z * 0x111111;
	if (point->color > 0xFFFFFF)
		point->color = 0xFFFFFF;
	if (point->color < 0x000000)
		point->color = 0x000000;
}

void	key_translate(int key, t_scene *scene)
{
	if (key == 0x7B)
		scene->tr_x -= 0.5;
	if (key == 0x7C)
		scene->tr_x += 0.5;
	if (key == 0x7D)
		scene->tr_y += 0.5;
	if (key == 0x7E)
		scene->tr_y -= 0.5;
}

void	key_rotate(int key, t_scene *scene)
{
	if (key == 0x7D)
		scene->rot_x -= 0.04;
	if (key == 0x7E)
		scene->rot_x += 0.04;
	if (key == 0x7B)
		scene->rot_y -= 0.04;
	if (key == 0x7C)
		scene->rot_y += 0.04;
	if (key == 32)
		scene->rot_z += 0.04;
	if (key == 34)
		scene->rot_z -= 0.04;
}

void	key_scale(int key, t_scene *scene)
{
	if (key == 0x7E)
		scene->scale += 0.5;
	if (key == 0x7D)
		scene->scale -= 0.5;
}

void	key_event(int key, t_scene *scene)
{
	if (scene->state == TRANSLATE)		
		key_translate(key, scene);
	if (scene->state == ROTATE)		
		key_rotate(key, scene);
	if (scene->state == SCALE)		
		key_scale(key, scene);
}

int	deal_key(int key, t_scene *scene)
{
	key_event(key, scene);
	if (key == 53)
		exit(0);
	if (key == 49)
	{
		scene->state++;
		if (scene->state > SCALE)
			scene->state = TRANSLATE;
	}
	if (key == 122)
	{
		scene->rot_x = 0;
		scene->rot_y = 0;
		scene->rot_z = 0;
	}
	if (key == 120)
	{
		scene->rot_x = 1.04;
		scene->rot_y = -0.48;
		scene->rot_z = 0.4;
	}
	if (key == 99)
		map_iter(scene, change_color, 2);
	fill_img(scene, scene->bg_color);
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
	show_map(scene);
	draw_scene(scene);
	mlx_put_image_to_window(scene->mlx_ptr, scene->win_ptr, scene->img_ptr, 0, 0);
	mlx_key_hook(scene->win_ptr, deal_key, scene);
	draw_hud(scene);
	mlx_loop(scene->mlx_ptr);
	return (0);
}
