/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 14:41:48 by lugibone          #+#    #+#             */
/*   Updated: 2019/04/05 14:48:22 by lugibone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *t;
	t_list *cursor;

	t = NULL;
	cursor = NULL;
	if (!alst)
		return ;
	cursor = *alst;
	while (cursor)
	{
		t = cursor;
		cursor = cursor->next;
		(*del)(t, t->content_size);
	}
	*alst = NULL;
}
