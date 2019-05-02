/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 19:29:21 by lugibone          #+#    #+#             */
/*   Updated: 2019/04/04 19:29:28 by lugibone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int a, int fd)
{
	unsigned int b;

	b = a;
	if (a < 0)
	{
		ft_putchar_fd('-', fd);
		b = -a;
	}
	if (b >= 10)
	{
		ft_putnbr_fd(b / 10, fd);
		ft_putchar_fd(b % 10 + '0', fd);
	}
	if (b < 10)
		ft_putchar_fd(b % 10 + '0', fd);
}
