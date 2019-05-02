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

void	fill_img(int *img, int color)
{
	int i;
	int c;

	c = color;
	i = 0;	
	while(i < WIDTH * HEIGHT)
	{
		if (c <= 0)
			c = color;
		img[i] = c--;
		i++;
	}
}

int	deal_key(int key, void *param)
{
	ft_putstr("\n");
	ft_putnbr(key);
	return (0);
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
	win_ptr = mlx_new_window(mlx_ptr, WIDTH, HEIGHT, "hell World");
	
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

	mlx_loop(mlx_ptr);
	return (0);
}
