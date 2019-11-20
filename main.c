/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 19:24:42 by lugibone          #+#    #+#             */
/*   Updated: 2019/11/20 18:45:21 by lugibone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_scene *scene;

	scene = NULL;
	if (argc == 2 && (!(check_extension(argv[1], ".fdf"))))
		scene = init_scene(WIDTH, HEIGHT, argv[1], argv);
	else
		return (0);
	fill_img(scene, scene->bg_color);
//	show_map(scene);
	draw_scene(scene);
	mlx_put_image_to_window(scene->mlx_ptr,
scene->win_ptr, scene->img_ptr, 0, 0);
	mlx_key_hook(scene->win_ptr, deal_key, scene);
	draw_hud(scene);
	mlx_loop(scene->mlx_ptr);
	return (0);
}
