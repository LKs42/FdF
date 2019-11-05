#include "fdf.h"

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