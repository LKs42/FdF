/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 15:36:29 by lugibone          #+#    #+#             */
/*   Updated: 2019/04/26 14:59:53 by lugibone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define MAX_FD 5000
#define BUFF_SIZE 100

static char		*ft_free_join(char *s1, const char *s2)
{
	char	*s3;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	if (!(s3 = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		return (NULL);
	i = -1;
	while (s1[++i])
		s3[i] = s1[i];
	j = 0;
	while (s2[j])
	{
		s3[i] = s2[j];
		i++;
		j++;
	}
	s3[i] = '\0';
	ft_strdel(&s1);
	return (s3);
}

char			*ft_n_strndup(char *str, char *dest, size_t n)
{
	size_t	i;

	if (!(dest = ft_strnew(sizeof(char) * n)))
		return (0);
	i = 0;
	while (i < n && str[i])
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void			ft_spacesaver(char **stock, char **tmp, size_t i)
{
	*tmp = *stock;
	*stock = ft_strdup(*stock + i + 1);
	free(*tmp);
}

int				get_next_line(const int fd, char **line)
{
	size_t			i;
	int				readsize;
	char			buffer[BUFF_SIZE + 1];
	static char		*stock = NULL;
	char			*tmp;

	if (fd < 0 || fd > MAX_FD || !line || !BUFF_SIZE || read(fd, stock, 0) < 0)
		return (-1);
	(!stock) ? stock = ft_strnew(0) : 0;
	while ((readsize = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[readsize] = '\0';
		if (!(stock = ft_free_join(stock, buffer)))
			return (-1);
		if (ft_strchr(stock, '\n'))
			break ;
	}
	if ((readsize < BUFF_SIZE) && (ft_strlen(stock) == 0))
		return (0);
	i = 0;
	while (stock[i] != '\n' && stock[i])
		i++;
	*line = ft_n_strndup(stock, *line, i);
	(i < ft_strlen(stock)) ? ft_spacesaver(&stock, &tmp, i) : ft_strdel(&stock);
	return (1);
}
