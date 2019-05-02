/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 16:32:29 by lugibone          #+#    #+#             */
/*   Updated: 2019/04/03 17:06:11 by lugibone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*sp1;
	unsigned char	*sp2;

	sp1 = (unsigned char*)s1;
	sp2 = (unsigned char*)s2;
	while (n--)
	{
		if (*sp1 != *sp2)
		{
			return (*sp1 - *sp2);
		}
		else
		{
			sp1++;
			sp2++;
		}
	}
	return (0);
}
