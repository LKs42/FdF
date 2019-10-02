/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 15:49:46 by lugibone          #+#    #+#             */
/*   Updated: 2019/10/02 12:43:43 by lugibone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <libft.h>

void	loop(char **curr_line)
{

	for (int i = 0; curr_line[i]; i++)
	{
			ft_putnbr(ft_atoi(curr_line[i]));
		for (int j = 0; curr_line[i][j]; j++)
		{
			//ft_putchar(curr_line[i][j]);
			//ft_putnbr(ft_atoi(curr_line[i]));
			//ft_putchar(' ');
		}
			ft_putchar(' ');
	}
		ft_putchar('\n');
}
	

void	fileread(char *str, int fd)
{
	char line;
	char **curr_line;

	line = 0;
	while(line++ < 15)
	{
		//ft_putendl(ft_str_read_line(str, fd));
		ft_str_read_line(str, fd);
		curr_line = ft_split(str, " \n");
		loop(curr_line);
	}
}

int	main(int argc, char **argv)
{
	char *str;
   	str	= malloc(sizeof(char) * 1000);
	if (argc == 2)
		fileread(str, open(argv[1], O_RDONLY));
	return (0);
}
