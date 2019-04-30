#include "mlx.h"
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

void fill_pixel(char *my_image_string, int x, int y, int color)
{

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

int main()
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*mlx_image1;
	int	*str;
	int bpp;
	int sl;
	int endian;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, WIDTH, HEIGHT, "hell World");
	
	mlx_image1 = mlx_new_image(mlx_ptr, WIDTH, HEIGHT);
	str = (int*)mlx_get_data_addr(mlx_image1, &bpp, &sl, &endian);
//	ft_draw_something(mlx_ptr, mlx_image1, 200, 200, 100);
	fill_img(str, 1000000);
	mlx_put_image_to_window(mlx_ptr, win_ptr, mlx_image1, 0, 0);

	//mlx_pixel_put(mlx_ptr, win_ptr, i, j, 255255255);

	mlx_loop(mlx_ptr);
	return (0);
}
