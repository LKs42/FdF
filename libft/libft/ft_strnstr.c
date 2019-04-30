/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <lugibone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:01:17 by lugibone          #+#    #+#             */
/*   Updated: 2019/04/17 13:56:31 by lugibone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	unsigned int i;
	unsigned int j;

	i = 0;
	if ((int)ft_strlen(to_find) == 0)
		return ((char*)str);
	while (str[i] && i < len)
	{
		j = 0;
		while (str[i + j] == to_find[j] && str[i + j] && (i + j) < len)
		{
			j++;
			if (to_find[j] == '\0')
				return ((char*)str + i);
		}
		i++;
	}
	return (0);
}
