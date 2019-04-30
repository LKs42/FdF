/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 15:43:54 by lugibone          #+#    #+#             */
/*   Updated: 2019/04/05 19:02:40 by lugibone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_is_printable(char c, char *cs)
{
	int i;

	i = -1;
	while (cs[++i])
	{
		if (c == cs[i])
			return (2);
	}
	if (c > ' ' && c < 127)
		return (1);
	else
		return (0);
}

static int		ft_nbchar(char *str, char *cs)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (ft_is_printable(str[i], cs) == 2)
			i++;
		while (ft_is_printable(str[i], cs) != 2 && str[i])
		{
			j++;
			i++;
		}
	}
	return (j);
}

static int		ft_nbw(char *str, int i, char *cs)
{
	int j;

	j = 0;
	while (str[i] && ft_is_printable(str[i], cs) != 2)
	{
		j++;
		i++;
	}
	return (j);
}

static char		**ft_loop(char *str, int i, char **tab, char *cs)
{
	int k;
	int j;

	j = 0;
	while (str[i])
	{
		while (str[i] && ft_is_printable(str[i], cs) == 2)
			i++;
		if (str[i])
		{
			k = 0;
			if (!(tab[j] = (char*)malloc(sizeof(char) * ft_nbw(str, i, cs))))
				return (0);
			while (str[i] && ft_is_printable(str[i], cs) != 2)
			{
				tab[j][k] = str[i];
				i++;
				k++;
			}
			tab[j][k] = '\0';
			j++;
		}
	}
	tab[j] = 0;
	return (tab);
}

char			**ft_split(char *str, char *charset)
{
	char	**tab;
	int		i;

	i = 0;
	if (!(tab = (char**)malloc(sizeof(char*) * ft_nbchar(str, charset) + 1)))
		return (0);
	return (ft_loop(str, i, tab, charset));
}
