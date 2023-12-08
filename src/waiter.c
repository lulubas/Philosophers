/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:49:32 by lbastien          #+#    #+#             */
/*   Updated: 2023/12/04 21:49:34 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philosophers.h"

void	*waiter_thread(void *args)
{
	t_info	*info;
	int		i;

	i = 0;
	info = (t_info *)args;
	while (dinner_is_on(info))
	{
		wait_for_next_round(info);
		while (i < info->philo_num)
		{
			info->philos[i]->can_eat = check_can_eat(info->philos[i]);
			if (info->philo_num > 1)
				info->philos[i]->next_round = true;
			i++;
		}
		i = 0;
		usleep(20);
	}
	return (NULL);
}

bool	check_can_eat(t_philo *philo)
{
	int		*index;
	int		philo_num;
	bool	can_eat_next;

	index = &philo->index;
	philo_num = philo->info->philo_num;
	if (*index % 2 == 0 && *index != philo_num - 1)
		can_eat_next = true;
	else
		can_eat_next = false;
	*index = (*index + 1) % philo_num;
	return (can_eat_next);
}

void	wait_for_next_round(t_info *info)
{
	int		i;

	i = 0;
	while (dinner_is_on(info))
	{
		if (info->philos[i]->next_round == false)
			i++;
		else
			usleep(20);
		if (i == info->philo_num)
			return ;
	}
}
