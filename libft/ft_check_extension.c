/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_extension.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:10:27 by lugibone          #+#    #+#             */
/*   Updated: 2019/06/04 17:11:52 by lugibone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_check_extension(char *str, char *str2)
{
	int i;
	int strlen;

	i = 0;
	strlen = ft_strlen(str);
	i = strlen - 1;
	while (i >= 0)
	{
		if (str[i] == '.')
		{
			if (ft_strcmp(str + i, str2) == 0)
				return (1);
			else
				return (0);
		}
		i--;
	}
	return (0);
}
