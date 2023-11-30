/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:07:13 by lbastien          #+#    #+#             */
/*   Updated: 2023/01/23 17:31:51 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/libft.h"

int	ft_putstr(const char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (!str)
	{
		count = ft_putstr("(null)");
		return (count);
	}
	else
	{
		while (str[i])
		{
			count += ft_putchar(str[i]);
			i++;
		}
	}
	return (count);
}
