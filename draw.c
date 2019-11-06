/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <lugibone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 18:52:26 by lugibone          #+#    #+#             */
/*   Updated: 2019/11/06 14:11:48 by lugibone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	state_hud(t_scene *scene)
{
	if (scene->state == TRANSLATE)
		mlx_string_put(scene->mlx_ptr,
scene->win_ptr, 30, 130, 0xFFFFFF, "TRANSLATION");
	if (scene->state == ROTATE)
		mlx_string_put(scene->mlx_ptr,
scene->win_ptr, 30, 130, 0xFFFFFF, "ROTATION");
	if (scene->state == SCALE)
		mlx_string_put(scene->mlx_ptr,
scene->win_ptr, 30, 130, 0xFFFFFF, "SCALING");
}

void	draw_hud(t_scene *scene)
{
	mlx_string_put(scene->mlx_ptr, scene->win_ptr,
30, 50, 0xFFFFFF, scene->title);
	mlx_string_put(scene->mlx_ptr, scene->win_ptr,
30, 70, 0xFFFFFF, "R: ");
	mlx_string_put(scene->mlx_ptr, scene->win_ptr,
30, 90, 0xFFFFFF, "G: ");
	mlx_string_put(scene->mlx_ptr, scene->win_ptr,
30, 110, 0xFFFFFF, "B: ");
	mlx_string_put(scene->mlx_ptr, scene->win_ptr,
50, 70, 0xFFFFFF, ft_itoa_base(rgb_r(scene->bg_color), 10));
	mlx_string_put(scene->mlx_ptr, scene->win_ptr,
50, 90, 0xFFFFFF, ft_itoa_base(rgb_g(scene->bg_color), 10));
	mlx_string_put(scene->mlx_ptr, scene->win_ptr,
50, 110, 0xFFFFFF, ft_itoa_base(rgb_b(scene->bg_color), 10));
	state_hud(scene);
}

void	draw_scene(t_scene *scene)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (++i < scene->map_h)
	{
		while (++j < scene->map_w - 1)
			liner(scene->str, ft_rot_matrix(&scene->map[i][j], scene, scene->point_a), ft_rot_matrix(&scene->map[i][j + 1], scene, scene->point_b));
		j = -1;
	}
	i = -1;
	while (++i < scene->map_h - 1)
	{
		while (++j < scene->map_w)
			liner(scene->str, ft_rot_matrix(&scene->map[i][j], scene, scene->point_a), ft_rot_matrix(&scene->map[i + 1][j], scene, scene->point_b));
		j = -1;
	}
}
