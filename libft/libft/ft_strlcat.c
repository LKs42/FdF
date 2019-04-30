/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <lugibone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 14:50:38 by lugibone          #+#    #+#             */
/*   Updated: 2019/04/02 15:34:21 by lugibone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t ldest;
	size_t lsrc;
	size_t i;

	ldest = 0;
	lsrc = 0;
	i = 0;
	while (dest[ldest] != '\0')
		ldest++;
	while (src[lsrc] != '\0')
		lsrc++;
	if (size < ldest)
		return (size + lsrc);
	while (src[i] != '\0' && (ldest + i + 1) < size)
	{
		dest[ldest + i] = src[i];
		i++;
	}
	dest[ldest + i] = '\0';
	return (ldest + lsrc);
}
