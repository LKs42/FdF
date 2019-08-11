/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 14:46:58 by lugibone          #+#    #+#             */
/*   Updated: 2019/05/29 13:43:10 by lugibone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"

typedef struct	s_scene
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		*string;
	int bpp;
	int sl;
	int endian;
	int map_w;
	int map_h;
	float rot_x;
	float rot_y;
	float rot_z;
}				t_scene;

typedef struct s_point
{
	int x;
	int y;
	int z;
}				t_point;
