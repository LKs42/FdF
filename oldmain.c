#include "mlx.h"
#include "libft.h"
#include <unistd.h>
#include <math.h>
#define WIDTH 2000 
#define HEIGHT 2000
#define ABS(N) ((N<0)?(-N):(N))

void fill_pixel_point(int *my_image_string, t_point *p, int color)
{
	int i;

	i = p->x + WIDTH*p->y;
	my_image_string[i] = color;
}

void fill_pixel(int *my_image_string, int x, int y, int color)
{
	int i;

	i = x + WIDTH*y;
	my_image_string[i] = color;
}

void fill_pixel_3d(int *my_image_string, int x, int y, int z, int color)
{
	int i;

	i = x + WIDTH*y + WIDTH * HEIGHT * z;
	my_image_string[i] = color;
}

float	lerp(float start, float end, float t)
{
	return (start + t * (end-start));
}

void	fill_square(int *img, int x, int y, int color)
{
	int i = 0;
	int j = 0;
	int size = 200;
	while (i < size)
	{
		while (j < size)
		{
			fill_pixel(img, x + i, y + j, color);
			j++;
		}
		i++;
		j = 0;
	}
}

void	fill_img(t_scene *param, int color)
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

float	ft_fmax(float a, float b)
{
	if (a >= b)
		return (a);
	return (b);
}

int	roundNo(float n)
{
	return (n < 0 ? n -0.5 : n + 0.5);
}

t_point	*round_point(t_point *p0)
{
	t_point *res;
	res = malloc(sizeof(t_point));
	res->x = roundNo(res->x);
	res->y = roundNo(res->y);
	return (res);
}

t_point	*lerp_point(t_point *a, t_point *b, float t)
{
	t_point *res;

	res = malloc(sizeof(t_point));
	res->x = lerp(a->x, b->x, t);
	res->y = lerp(a->y, b->y, t);
	return (res);
}

float	diagonal_dist(float ax, float ay, float bx, float by)
{
	float dx;
	float dy;

	dy = by - ay;
	dx = bx - ax;
	return (ft_fmax(ABS(dx), ABS(dy)));
}

void liner2(int *img, int x0, int y0, int x1, int y1, int color) {
	int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
	int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
	int err = (dx>dy ? dx : -dy)/2, e2;

	while(!(x0==x1 && y0==y1))
	{
		fill_pixel(img, x0, y0, color);
		e2 = err;
		if (e2 >-dx) { err -= dy; x0 += sx; }
		if (e2 < dy) { err += dx; y0 += sy; }
	}
}

void liner(int *img, t_point *a, t_point *b, int color) {
	int x0 = a->x;
	int x1 = b->x;
	int y0 = a->y;
	int y1 = b->y;

	int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
	int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
	int err = (dx>dy ? dx : -dy)/2, e2;

	while(!(x0==x1 && y0==y1))
	{
		fill_pixel(img, x0, y0, color);
		e2 = err;
		if (e2 >-dx) { err -= dy; x0 += sx; }
		if (e2 < dy) { err += dx; y0 += sy; }
	}
}

void	draw_scene(t_scene *scene, int a)
{
	int i;

	i = -1;
	while (++i < a * a)
		if (!(i % a == 0))
			liner(scene->str, scene->map[i - 1], scene->map[i], 0x00FF00);
	i = -1;
	while (++i + a < a * a)
		liner(scene->str, scene->map[i], scene->map[i + a], 0xFF0000);
}

void	rotate_z(t_scene *scene, int ag, int a)
{
	float xp;
	float yp;
	for (int i = 0; i < a * a; i++)
		{
			//xp = scene->map[i]->x + 1000;
			xp = scene->map[i]->x * cos(ag) - scene->map[i]->y * sin(ag);
			yp = scene->map[i]->x * sin(ag) + scene->map[i]->y * cos(ag);
			scene->map[i]->x = xp;
			scene->map[i]->y = yp;
		}
}

void	rotate_y(t_scene *scene, int ag, int a)
{
	float xp;
	float zp;
	for (int i = 0; i < a * a; i++)
		{
			//xp = scene->map[i]->x + 1000;
			xp = scene->map[i]->x * cos(ag) - scene->map[i]->y * sin(ag);
			zp = - (scene->map[i]->x) * sin(ag) + scene->map[i]->z * cos(ag);
			scene->map[i]->x = xp;
			scene->map[i]->z = zp;
		}
}

void	translate_x(t_scene *scene, int a, int dist)
{
	for (int i = 0; i < a * a; i++)
			scene->map[i]->x += dist;
}


void	translate_y(t_scene *scene, int a, int dist)
{
	for (int i = 0; i < a * a; i++)
			scene->map[i]->y += dist;
}

int	deal_key(int key, t_scene *scene)
{	
	if (key == 53)
		exit(0);
	if (key == 12)
		rotate_z(scene, 1, 10);
	if (key == 124)
		translate_x(scene, 10, 10);
	if (key == 123)
		translate_x(scene, 10, -10);
	if (key == 125)
		translate_y(scene, 10, 10);
	if (key == 126)
		translate_y(scene, 10, -10);
	fill_img(scene, 0x181818);
	draw_scene(scene, 10);
	mlx_put_image_to_window(scene->mlx_ptr, scene->win_ptr, scene->img_ptr, 0, 0);
	ft_putstr("\n");
	ft_putnbr(key);
	return (0);
}

t_scene	*init_scene(int w, int h, void *mlx, char *str)
{
	t_scene *scene;

	scene = malloc(sizeof(t_scene));
	scene->win_height = h;
	scene->win_width = w;
	scene->mlx_ptr = mlx;
	scene->title = str;
	scene->win_ptr = mlx_new_window(scene->mlx_ptr, w, h, str);
	return (scene);
}

void	ft_initpoints(t_point **points, int nb)
{
	int i = 0;
	int j = 0;
	int cp = 0;
	int space = 50;
	int xo = space;
	int yo = space;
	int zo = 10;
	while (i < nb)
	{
		while (j < nb)
		{
			points[cp] = malloc(sizeof(t_point));
			points[cp]->x = xo;
			points[cp]->y = yo;
			points[cp]->z = zo;
			xo += space;
			zo+= 10;
			cp++;
			j++;
		}
		j = 0;
		yo += space;
		xo = space;
		i++;
	}
}
int main(int argc, char **argv)
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*mlx_image1;
	int	*str;
	int a = 10;

	mlx_ptr = mlx_init();
	t_scene *scene;
	scene = init_scene(WIDTH, HEIGHT, mlx_ptr, "hell world");
	scene->img_ptr = mlx_new_image(scene->mlx_ptr, scene->win_width, scene->win_height);
	str = (int*)mlx_get_data_addr(scene->img_ptr, &scene->bpp, &scene->sl, &scene->endian);
	scene->str = str;
	fill_img(scene, 0x181818);

	int ag = 0;
	if (argc == 2)
		ag = atoi(argv[1]);

	scene->map = malloc(sizeof(t_point) * a * a);
	ft_initpoints(scene->map, a);

	draw_scene(scene, a);

	mlx_put_image_to_window(scene->mlx_ptr, scene->win_ptr, scene->img_ptr, 0, 0);
	mlx_key_hook(scene->win_ptr, deal_key, scene);
	mlx_loop(mlx_ptr);
	return (0);
}
