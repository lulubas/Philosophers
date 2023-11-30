/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:33:33 by lbastien          #+#    #+#             */
/*   Updated: 2022/11/02 21:19:36 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/libft.h"

t_int	*ft_intlst_new(int num)
{
	t_int	*lst;

	lst = (t_int *)malloc(sizeof(t_int));
	if (!lst)
		return (0);
	lst->num = num;
	lst->next = NULL;
	return (lst);
}
