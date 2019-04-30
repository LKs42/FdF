/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 16:06:20 by lugibone          #+#    #+#             */
/*   Updated: 2019/04/25 16:42:55 by lugibone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_read(char *str, int fd)
{
	int		ret;
	char	buf[2];
	int		j;
	int		i;

	i = 0;
	j = -1;
	while ((ret = read(fd, buf, 2)) > 0)
	{
		buf[ret] = '\0';
		while (++j < 2)
		{
			str[i] = buf[j];
			i++;
		}
		j = -1;
	}
	str[i] = '\0';
	return (str);
}
