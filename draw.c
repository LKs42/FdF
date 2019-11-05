#include "fdf.h"

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