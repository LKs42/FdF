/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 14:46:58 by lugibone          #+#    #+#             */
/*   Updated: 2019/05/15 18:06:45 by lugibone         ###   ########.fr       */
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
}				t_scene;

typedef struct s_point
{
	int x;
	int y;
	int z;
}				t_point;
