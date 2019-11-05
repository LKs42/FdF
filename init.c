#include "fdf.h"

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