/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 16:12:48 by lugibone          #+#    #+#             */
/*   Updated: 2019/04/05 17:04:21 by lugibone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*des;
	char	*sr;
	size_t	i;

	des = (char *)dest;
	sr = (char *)src;
	i = -1;
	if (sr < des)
		while ((int)(--n) >= 0)
			*(des + n) = *(sr + n);
	else
		while (++i < n)
			*(des + i) = *(sr + i);
	return (dest);
}
