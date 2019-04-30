/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 13:50:08 by lugibone          #+#    #+#             */
/*   Updated: 2019/04/05 17:04:32 by lugibone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *node;

	if (!(node = (t_list*)malloc(sizeof(t_list) + content_size)))
		return (NULL);
	if (content == NULL)
	{
		node->content = NULL;
		node->content_size = 0;
	}
	else
	{
		node->content = malloc(sizeof(content) + content_size);
		if (node->content == NULL)
			return (NULL);
		ft_memcpy((node->content), content, sizeof(content) + content_size);
		node->content_size = content_size;
	}
	node->next = NULL;
	return (node);
}
