/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <lugibone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 14:56:37 by lugibone          #+#    #+#             */
/*   Updated: 2019/04/17 13:56:57 by lugibone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char *ret;

	ret = 0;
	if (*s == (char)c)
		ret = (char*)s;
	while (*s++)
	{
		if (*s == (char)c)
			ret = (char*)s;
	}
	return (ret);
}
