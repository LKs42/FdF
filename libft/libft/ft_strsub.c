/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:18:17 by lugibone          #+#    #+#             */
/*   Updated: 2019/04/05 18:57:10 by lugibone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*result;

	if (s == NULL)
		return (NULL);
	i = (unsigned int)ft_strlen((char*)s);
	if (((unsigned int)start + (unsigned int)len) > i)
		return (NULL);
	result = ft_strnew(len);
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < (unsigned int)len && s[start])
	{
		result[i] = s[start];
		start++;
		i++;
	}
	return (result);
}
