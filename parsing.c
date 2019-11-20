/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <lugibone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 19:27:56 by lugibone          #+#    #+#             */
/*   Updated: 2019/11/20 17:58:46 by lugibone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	check_extension(char *str, char *extension)
{
	return (ft_strcmp(str + ft_strlen(str)
		- ft_strlen(extension), extension) == 0) ? 0 : 1;
}

int	check_line(char *str, t_scene *scene)
{
	int i;
	char **split;
	i = 0;
	while (str[i])
	{
		if (!(ft_isdigit(str[i])) && str[i] != ' ' && str[i] != '\n' && str[i] != '-')
		{
			return (0);
		}
		i++;
	}
	i = 0;
	split = ft_split_char(str, ' ');
	while (split[i])
		i++;
	if (scene->map_w != 0)
		if (i != scene->map_w)
		{
			free2d_array(split);
			return (0);
		}
	if (scene->map_w == 0)
		scene->map_w = i;
	free2d_array(split);
	return (1);
}
