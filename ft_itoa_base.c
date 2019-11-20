/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <lugibone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 14:44:37 by lugibone          #+#    #+#             */
/*   Updated: 2019/11/20 18:58:03 by lugibone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strrev(char *str)
{
	int		i;
	int		j;
	char	tmp;

	tmp = 0;
	i = 0;
	j = ft_strlen(str) - 1;
	while (i < j)
	{
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
		i++;
		j--;
	}
}

int		ft_nb_digit(int nbr)
{
	int i;

	i = 0;
	while (nbr)
	{
		i++;
		nbr /= 10;
	}
	return (i);
}

char	*ft_itoa_base(int value, int base)
{
	char	*base16;
	char	*res;
	int		i;
	int		nb;

	i = 0;
	base16 = "0123456789ABCDEF";
	if (!(res = malloc(sizeof(char) * ft_nb_digit(value))))
		return (0);
	if (value == 0 || base == 1)
	{
		res = "0\0";
		return (res);
	}
	nb = value;
	while (nb > 0)
	{
		res[i] = base16[nb % base];
		nb /= base;
		i++;
	}
	res[i] = '\0';
	ft_strrev(res);
	return (res);
}
