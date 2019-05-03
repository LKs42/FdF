#include "mlx.h"
#include "libft.h"
#include <unistd.h>
#define WIDTH 1280
#define HEIGHT 720

void	ft_draw_something(void *mlx_ptr, void *win_ptr, int x, int y, int size)
{
	int i;
	int j;
	i = x;
	j = y;
	int a;
	int b;
	a = 0;
	b = 0;
	while (a < size)
	{
		while (b < size)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, i + a, j + b, 255255255);
			b++;
		}
		b = 0;
		a++;
	}
}

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

#define ABS(N) ((N<0)?(-N):(N))

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

void	line(int *img, t_point *a, t_point *b, int color)
{
	float n;
	float t;
	n = diagonal_dist(a->x, a->y, b->x, b->y);
	for (int step = 0; step <= n; step++)
	{
		t = n == 0 ? 0.0 : step / n;
		fill_pixel_point(img, round_point(lerp_point(a, b, t)), color);
	}
}

void liner(int *img, int x0, int y0, int x1, int y1) {

	int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
	int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
	int err = (dx>dy ? dx : -dy)/2, e2;

	for(;;){
		fill_pixel(img, x0, y0, 10);
		if (x0==x1 && y0==y1) break;
		e2 = err;
		if (e2 >-dx) { err -= dy; x0 += sx; }
		if (e2 < dy) { err += dx; y0 += sy; }
	}
}

int	deal_key(int key, t_scene *scene)
{	
	fill_img(scene, 11894015);

	//fill_pixel_point(scene->str, p1, 1000);
	//line(scene->str, p1, p2, 1000);
	//fill_square(scene->str, key, key, key);
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

int main()
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*mlx_image1;
	void	*mlx_image2;
	int	*str;
	int	*str2;
	int bpp;
	int sl;
	int endian;
	int a = 100;

	mlx_ptr = mlx_init();
	t_scene *scene;
	scene = init_scene(1280, 720, mlx_ptr, "hell world");
	scene->img_ptr = mlx_new_image(scene->mlx_ptr, scene->win_width, scene->win_height);
	str = (int*)mlx_get_data_addr(scene->img_ptr, &bpp, &sl, &endian);
	scene->str = str;
	fill_img(scene, 11894015);



	t_point *p1;
	t_point *p2;
	p1 = malloc(sizeof(t_point));
	p2 = malloc(sizeof(t_point));
	p1->x = 1000;
	p2->x = 100;
	p2->y = 200;
	p1->y = 250;

	liner(scene->str, 100, 100, 100, 500);
	liner(scene->str, 100, 100, 500, 100);
	liner(scene->str, 100, 500, 500, 500);
	liner(scene->str, 500, 500, 500, 100);

	mlx_put_image_to_window(scene->mlx_ptr, scene->win_ptr, scene->img_ptr, 0, 0);
	mlx_key_hook(scene->win_ptr, deal_key, scene);

	/*	
		mlx_image1 = mlx_new_image(mlx_ptr, WIDTH, HEIGHT);
		mlx_image2 = mlx_new_image(mlx_ptr, WIDTH, HEIGHT);
		str = (int*)mlx_get_data_addr(mlx_image1, &bpp, &sl, &endian);
		str2 = (int*)mlx_get_data_addr(mlx_image2, &bpp, &sl, &endian);
	//	ft_draw_something(mlx_ptr, mlx_image1, 200, 200, 100);
	fill_img(str, 11894015);
	fill_square(str2, 0, 0, 11894015);
	mlx_put_image_to_window(mlx_ptr, win_ptr, mlx_image1, 0, 0);
	mlx_put_image_to_window(mlx_ptr, win_ptr, mlx_image2, a, 100);

	//mlx_pixel_put(mlx_ptr, win_ptr, i, j, 255255255);

	mlx_key_hook(win_ptr, deal_key, (void*)0);
	*/
	mlx_loop(mlx_ptr);
	return (0);
}