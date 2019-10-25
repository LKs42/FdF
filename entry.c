/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 15:49:46 by lugibone          #+#    #+#             */
/*   Updated: 2019/10/25 18:14:03 by lugibone         ###   ########.fr       */
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

void	loop(char **curr_line, t_point **line, int y, int size)
{
	int x;

	x = 0;
	while (curr_line[x] && curr_line[x][0] != '\0')
	{
		line[y] = malloc(sizeof(t_point *) * size);
		line[y][x].x = (float)x;
		line[y][x].y = (float)y;
		line[y][x].z = (float)ft_atoi(curr_line[x]);
		x++;
	}
}
	
t_point	**fileread(int fd)
{
	char **curr_line;
	int	y;
	char *str;
	t_point **map;
	
	map = NULL;
	str = malloc(sizeof(char) * 10000);	
	map = malloc(sizeof(char) * 10000);	
	y = 0;
	while(curr_line[y])
	{
		ft_str_read_line(str, fd);
		curr_line = ft_split(str, " \n");
		loop(curr_line, map, y, ft_strlen(str));
		y++;
	}
	map[y] = NULL;
	free(str);
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
		while(/*scene->map[i][j] != NULL &&*/ j < 20)
		{
			ft_putstr("i: ");
			ft_putnbr(i);
			ft_putstr(" j: ");
			ft_putnbr(j);
			ft_putstr("          | x: ");
			ft_putnbr(scene->map[i][j].x);
			ft_putstr(" y: ");
			ft_putnbr(scene->map[i][j].y);
			ft_putstr(" z: ");
			ft_putnbr(scene->map[i][j].z);
			ft_putstr(" |\n");
			j++;
		}
	j = 0;
	i++;
	}
}

t_scene *init_scene(int w, int h, char *str, char **argv)
{
        t_scene *scene;

        scene = malloc(sizeof(t_scene) * 5);
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
	fill_img(scene, 0xFF00FF);
	return (0);
}

int	main(int argc, char **argv)
{
	t_scene *scene;

	scene = NULL;
	if (argc == 2)
		scene = init_scene(WIDTH, HEIGHT, TITLE, argv);
	fill_img(scene, scene->bg_color);

	mlx_put_image_to_window(scene->mlx_ptr, scene->win_ptr, scene->img_ptr, 0, 0);
 	mlx_key_hook(scene->win_ptr, deal_key, scene);
	mlx_loop(scene->mlx_ptr);
	return (0);
}
