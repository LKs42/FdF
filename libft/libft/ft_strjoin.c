/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 15:04:44 by lugibone          #+#    #+#             */
/*   Updated: 2019/04/05 18:37:20 by lugibone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*joined;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen((char*)s1) + ft_strlen((char*)s2) + 1;
	joined = ft_strnew(len);
	if (joined == NULL)
		return (NULL);
	ft_strcat((char*)joined, (char*)s1);
	ft_strcat((char*)joined, (char*)s2);
	return (joined);
}
