#include <unistd.h>
#include <math.h>
#include "libft.h"
#include "mlx.h"
#include <fcntl.h>
#define WIDTH 2000 
#define HEIGHT 2000
#define ABS(N) ((N<0)?(-N):(N))

typedef union u_mat4
{
	struct s_mat4_data
	{
		float m00;
		float m01;
		float m02;
		float m03;
		float m10;
		float m11;
		float m12;
		float m13;
		float m20;
		float m21;
		float m22;
		float m23;
		float m30;
		float m31;
		float m32;
		float m33;
	}		d;
	float m[4][4];
}		t_mat4;

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

void	ft_rotation_matrix(t_point *point, float angle, t_point *new_point)
{
	float focale;

	focale = 1;
	new_point->x = (focale * point->x)/point->z;
	new_point->y = (focale * point->y)/point->z;
}

t_point *ft_rot_x(t_point *point, t_scene *scene, t_point *new_point)
{
	float ag;

	ag = scene->rot_x;

	new_point->x = point->x;
	new_point->y = point->y * cos(ag) - point->z * sin(ag);
	new_point->z = point->y * sin(ag) + point->z * cos(ag);

	return (new_point);
}


t_point *ft_rot_y(t_point *point, t_scene *scene, t_point *new_point)
{
	float ag;

	ag = scene->rot_y;

	new_point->x = point->x * cos(ag) + point->z * sin(ag);
	new_point->y = point->y;
	new_point->z = -(point->x) * sin(ag) + point->z * cos(ag);

	return (new_point);
}


t_point *ft_rot_z(t_point *point, t_scene *scene, t_point *new_point)
{
	float ag;

	ag = scene->rot_z;

	new_point->x = point->x * cos(ag) - point->y * sin(ag);
	new_point->y = point->x * sin(ag) + point->y * cos(ag);
	new_point->z = point->z;

	return (new_point);
}

t_point	*ft_rot_matrix(t_point *point, t_scene *scene)
{
	float focale;
	t_point *new_point;
	float ag;

	ag = scene->rot_y;;
	new_point = malloc(sizeof(t_point));
	focale = scene->focale;

	ft_rot_x(point, scene, new_point);
	ft_rot_y(new_point, scene, new_point);
	ft_rot_z(new_point, scene, new_point);

	new_point->x = (focale * new_point->x)/point->z;
	new_point->y = (focale * new_point->y)/point->z;

	return (new_point);
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

void liner3(int *img, t_point *a, t_point *b, int color) {
	int dx;
	int dy; 
	int sx;
	int sy;
	int err;
	int e2;
	
	dx = abs((b->x) - (a->x));
       	sx = (a->x) < (b->x) ? 1 : -1;
	dy = abs((b->y) - (a->y));
	sy = (a->y) < (b->y) ? 1 : -1; 
	err = (dx > dy ? dx : -dy) /2;

	while (!((a->x) == (b->x) && (a->y) == (b->y)))
	{
		fill_pixel(img, (a->x), (a->y), color);
		e2 = err;
		if (e2 >-dx)
		{
			err -= dy;
			(a->x) += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			(a->y) += sy;
		}
	}
}

void	draw_scene(t_scene *scene, int a)
{
	int i;

	i = -1;
	while (++i < a * a)
		if (!(i % a == 0))
			liner(scene->str, ft_rot_matrix(scene->map[i - 1], scene), ft_rot_matrix(scene->map[i], scene), 0x00FF00);
	i = -1;
	while (++i + a < a * a)
		liner(scene->str, ft_rot_matrix(scene->map[i], scene), ft_rot_matrix(scene->map[i + a], scene), 0xFF0000);
}

int	deal_key(int key, t_scene *scene)
{	
	if (key == 53)
		exit(0);
	if (key == 32)
		exit(0);
	if (key == 97)
		scene->rot_x += 0.04;
	if (key == 122)
		scene->rot_x -= 0.04;
	if (key == 101)
		scene->rot_x = 0;
	if (key == 114)
		scene->rot_y += 0.04;
	if (key == 116)
		scene->rot_y -= 0.04;
	if (key == 121)
		scene->rot_y = 0;
	if (key == 117)
		scene->rot_z += 0.04;
	if (key == 105)
		scene->rot_z -= 0.04;
	if (key == 111)
		scene->rot_z = 0;
	if (key == 65362)
		scene->focale++;
	if (key == 65364)
		scene->focale--;
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
	scene->focale = 100;
	scene->rot_x = 0;
	scene->rot_y = 0;
	scene->rot_z = 0;
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
	int zo = 50;
	while (i < nb)
	{
		while (j < nb)
		{
			points[cp] = malloc(sizeof(t_point));
			points[cp]->x = xo;
			points[cp]->y = yo;
			points[cp]->z = zo;
			xo += space;
			zo += 0;
			cp++;
			j++;
		}
		j = 0;
		yo += space;
		xo = space;
		i++;
	}
}

void	ft_line_to_points(char *str, t_point **tab, int y)
{
	int x;
	int i;
	int j;

	j = 0;
	x = 0;
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		while (str[i] && str[i] == ' ')
			i++;
		tab[j]->x = x;
		tab[j]->y = y;
		tab[j]->z = ft_atoi(str + i);
		x++;
		j++;
		while (str[i] && ft_isdigit(str[i]))
			i++;
	}
}

t_point	**ft_file_to_points(char *str)
{
	t_point **points;
	int i;
	int j;
	int nbline;
	char **line;

	i = 0;
	j = 0;
	nbline = 0;
	line = ft_split_char(str, ' ');
	while (line[i][0])
	{
		if (line[i][0] == '\n')
		nbline++;
		else
			i++;
	}
	ft_putnbr(i);
	points = malloc(sizeof(t_point) * i);
	return (points);
}

int main(int argc, char **argv)
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*mlx_image1;
	int	*str;
	int a = 10;
	int fd;
	char *file;
	file = malloc(sizeof(char) * 1000);
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		ft_str_read(file, fd);
		ft_putendl(file);
	}
	
	mlx_ptr = mlx_init();
	t_scene *scene;
	scene = init_scene(WIDTH, HEIGHT, mlx_ptr, "hell world");
	scene->img_ptr = mlx_new_image(scene->mlx_ptr, scene->win_width, scene->win_height);
	str = (int*)mlx_get_data_addr(scene->img_ptr, &scene->bpp, &scene->sl, &scene->endian);
	scene->str = str;
	fill_img(scene, 0x181818);
	/*
	   t_point **tab;
	   tab = malloc(sizeof(t_point) * 1000);
	   ft_line_to_points(file, tab, 0);
	   */
	scene->map = malloc(sizeof(t_point) * a * a);
	ft_initpoints(scene->map, a);

	draw_scene(scene, a);
	
	mlx_put_image_to_window(scene->mlx_ptr, scene->win_ptr, scene->img_ptr, 0, 0);
	mlx_key_hook(scene->win_ptr, deal_key, scene);
	mlx_loop(mlx_ptr);
	return (0);
}
