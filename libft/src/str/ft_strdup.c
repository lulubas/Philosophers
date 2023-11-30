/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:03:21 by lbastien          #+#    #+#             */
/*   Updated: 2022/10/18 17:52:29 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/libft.h"

char	*ft_strdup(char *str)
{
	size_t	n;
	char	*ctr;

	n = ft_strlen(str);
	ctr = (char *)malloc(sizeof(char) * (n + 1));
	if (!ctr)
		return (0);
	ft_strlcpy(ctr, str, n + 1);
	return (ctr);
}
