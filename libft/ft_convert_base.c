/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convertbase.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 20:42:48 by lugibone          #+#    #+#             */
/*   Updated: 2019/04/10 16:24:19 by lugibone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_strrev(char *str)
{
	int		a;
	int		i;
	char	swap;

	i = 0;
	a = (int)ft_strlen(str) - 1;
	while (i < a)
	{
		swap = str[i];
		str[i] = str[a];
		str[a] = swap;
		i++;
		a--;
	}
	return (str);
}

static int		ft_recursive_power(int nb, int power)
{
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	return (nb * ft_recursive_power(nb, power - 1));
}

static char		*ft_convert(char *nbr, char *base_from,
char *base_to, char *result)
{
	int i;
	int j;
	int s;
	int base;

	base = (int)ft_strlen(base_from);
	j = ft_strlen(nbr);
	s = 0;
	i = 0;
	while (j-- > 0)
	{
		s += (nbr[i] - '0') * ft_recursive_power(base, j);
		i++;
	}
	base = (int)ft_strlen(base_to);
	i = 0;
	while (s > 0)
	{
		j = s / base;
		result[i] = base_to[s % base];
		s = j;
		i++;
	}
	result[i] = '\0';
	return (ft_strrev(result));
}

char			*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	char *result;

	if (!(result = malloc(sizeof(char) * 64)))
		return (NULL);
	return (ft_convert(nbr, base_from, base_to, result));
}
