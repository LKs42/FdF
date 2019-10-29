/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 15:49:46 by lugibone          #+#    #+#             */
/*   Updated: 2019/10/29 16:58:22 by lugibone         ###   ########.fr       */
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

void	loop(char **curr_line, t_point ***map, int y)
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
	map[y][x] = NULL;
}
	
t_point	***fileread(int fd)
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
		loop(curr_line, map, y);
		y++;
	}
	map[y] = NULL;
	return (map);
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
	scene->img_ptr = mlx_new_image(scene->mlx_ptr, scene->win_width, scene->win_height);
        scene->str = (int*)mlx_get_data_addr(scene->img_ptr, &scene->bpp, &scene->sl, &scene->endian);
	scene->map = fileread(open(argv[1], O_RDONLY));
	return (scene);
}

int	deal_key(int key, t_scene *scene)
{
	ft_putnbr(key);
	ft_putchar('\n');
	if (key == 49)
		exit(0);
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
	mlx_put_image_to_window(scene->mlx_ptr, scene->win_ptr, scene->img_ptr, 0, 0);
 	mlx_key_hook(scene->win_ptr, deal_key, scene);
	mlx_loop(scene->mlx_ptr);
	return (0);
}
