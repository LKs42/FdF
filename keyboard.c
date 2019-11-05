/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 19:21:29 by lugibone          #+#    #+#             */
/*   Updated: 2019/11/05 19:22:36 by lugibone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
		scene->rot_x += 0.04;
	if (key == 0x7E)
		scene->rot_x -= 0.04;
	if (key == 0x7B)
		scene->rot_y += 0.04;
	if (key == 0x7C)
		scene->rot_y -= 0.04;
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
}

int		deal_key(int key, t_scene *scene)
{
	key_event(key, scene);
	if (key == 53)
		exit(0);
	if (key == 99)
		map_iter(scene, change_color, 2);
	if (key == 49)
	{
		scene->state++;
		if (scene->state > SCALE)
			scene->state = TRANSLATE;
	}
	fill_img(scene, scene->bg_color);
	draw_scene(scene);
	mlx_put_image_to_window(scene->mlx_ptr,
scene->win_ptr, scene->img_ptr, 0, 0);
	draw_hud(scene);
	return (0);
}
