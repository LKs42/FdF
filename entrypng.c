/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 15:49:46 by lugibone          #+#    #+#             */
/*   Updated: 2019/10/16 18:08:26 by lugibone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <libft.h>

char	*str_read(char *str, int fd)
{
	int		ret;
	unsigned char	buf[2];
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
		//	ft_putchar(buf[j]);
			ft_putnbr(buf[j]);
			//ft_putnbr(atoi(buf));
			i++;
		}
		j = -1;
	}
	str[i] = '\0';
	return (str);
}

int	main(int argc, char **argv)
{
	char *str;
   	str	= malloc(sizeof(char) * 10000);
	if (argc == 2)
		str_read(str, open(argv[1], O_RDONLY));
	return (0);
}
