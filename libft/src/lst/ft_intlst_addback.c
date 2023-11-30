/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 18:08:35 by lbastien          #+#    #+#             */
/*   Updated: 2022/11/08 14:12:01 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/libft.h"

void	ft_intlst_addback(t_int **lst, t_int *new)
{
	t_int	*tmp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = ft_intlst_last(*lst);
	tmp->next = new;
	return ;
}
