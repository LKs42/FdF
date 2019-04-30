/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_read_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 16:48:07 by lugibone          #+#    #+#             */
/*   Updated: 2019/04/25 16:48:27 by lugibone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_read_line(char *str, int fd)
{
	int		ret;
	char	buf[2];
	int		j;
	int		sp;
	int		i;

	i = 0;
	sp = 0;
	j = -1;
	while (!sp && (ret = read(fd, buf, 2)) && buf[ret] != '\n')
	{
		buf[ret] = '\0';
		while (++j < 2 && !sp)
		{
			str[i] = buf[j];
			i++;
			if (buf[j] == '\n')
				sp = 1;
		}
		j = -1;
	}
	str[i] = '\0';
	return (str);
}
