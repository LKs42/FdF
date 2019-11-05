#include "fdf.h"

void fill_pixel(int *my_image_string, int x, int y, int color)
{
	int i;
	if (!(x <= 0 || y <= 0 || y >= HEIGHT || x >= WIDTH))
	{
		i = x + WIDTH * y;
		my_image_string[i] = color;
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