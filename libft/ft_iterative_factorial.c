/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <lugibone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 14:38:11 by lugibone          #+#    #+#             */
/*   Updated: 2019/02/10 15:04:50 by lugibone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_iterative_factorial(int nb)
{
	int result;
	int i;

	i = 0;
	result = 1;
	if (nb > 12 || nb < 0)
		return (0);
	while (i < nb)
	{
		result += result * i;
		i++;
	}
	return (result);
}
