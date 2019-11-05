/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 19:27:56 by lugibone          #+#    #+#             */
/*   Updated: 2019/11/05 19:28:03 by lugibone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	check_extension(char *str, char *extension)
{
	return (ft_strcmp(str + ft_strlen(str) -
ft_strlen(extension), extension) == 0) ? 0 : 1;
}
