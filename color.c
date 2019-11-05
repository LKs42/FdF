/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 18:49:41 by lugibone          #+#    #+#             */
/*   Updated: 2019/11/05 18:50:27 by lugibone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	change_color(t_point *point, float a)
{
	(void)a;
	point->color = point->z * 0x111111;
	if (point->color > 0xFFFFFF)
		point->color = 0xFFFFFF;
	if (point->color < 0x000000)
		point->color = 0x000000;
}

int		rgb_r(int color)
{
	return ((color & 0xFF0000) >> 16);
}

int		rgb_g(int color)
{
	return ((color & 0x00FF00) >> 8);
}

int		rgb_b(int color)
{
	return ((color & 0x0000FF));
}
