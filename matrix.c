#include "fdf.h"

t_point *ft_rot_x(t_point *point, t_scene *scene, t_point *new_point)
{
	float ag;
	t_point tmp;

	tmp.x = point->x;
	tmp.y = point->y;
	tmp.z = point->z;
	ag = scene->rot_x;
	new_point->x = tmp.x;
	new_point->y = tmp.y * cos(ag) - tmp.z * sin(ag);
	new_point->z = tmp.y * sin(ag) + tmp.z * cos(ag);
	return (new_point);
}


t_point *ft_rot_y(t_point *point, t_scene *scene, t_point *new_point)
{
	float ag;
	t_point tmp;

	tmp.x = point->x;
	tmp.y = point->y;
	tmp.z = point->z;
	ag = scene->rot_y;
	new_point->x = tmp.x * cos(ag) + tmp.z * sin(ag);
	new_point->y = tmp.y;
	new_point->z = -(tmp.x) * sin(ag) + tmp.z * cos(ag);
	return (new_point);
}


t_point *ft_rot_z(t_point *point, t_scene *scene, t_point *new_point)
{
	float ag;
	t_point tmp;

	tmp.x = point->x;
	tmp.y = point->y;
	tmp.z = point->z;
	ag = scene->rot_z;
	new_point->x = tmp.x * cos(ag) - tmp.y * sin(ag);
	new_point->y = tmp.x * sin(ag) + tmp.y * cos(ag);
	new_point->z = point->z;
	return (new_point);
}

void	ft_scale(t_point *point, float scale)
{
	point->x *= scale;
	point->y *= scale;
	point->z *= scale;
}

t_point	*ft_rot_matrix(t_point *point, t_scene *scene, t_point *new_point)
{
	float focale;
	float ag;

	ag = scene->rot_y;;
	focale = scene->focale;
	new_point->color = point->color;
	new_point->x = point->x - scene->map_w/2;
	new_point->y = point->y - scene->map_h/2;
	new_point->z = point->z;
	ft_rot_x(new_point, scene, new_point);
	ft_rot_y(new_point, scene, new_point);
	ft_rot_z(new_point, scene, new_point);
	new_point->x = new_point->x + scene->tr_x;
	new_point->y = new_point->y + scene->tr_y;
	new_point->z = new_point->z;
	ft_scale(new_point, scene->scale);
	return (new_point);
}