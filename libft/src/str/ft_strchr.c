/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:52:35 by lbastien          #+#    #+#             */
/*   Updated: 2022/10/11 16:38:41 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/libft.h"

char	*ft_strchr(const char *str, int c)
{
	char	a;

	if (!str)
		return (0);
	a = c;
	while (*str && *str != a)
		str++;
	if (*str != a)
		return (0);
	return ((char *)str);
}
