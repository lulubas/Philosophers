/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   workers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:49:32 by lbastien          #+#    #+#             */
/*   Updated: 2023/12/04 21:49:34 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
# include "../include/philisophers.h"

void	*init_monitor(void *args)
{
	t_info	*info;
	int		i;

	i = 0;
	info = (t_info *)args;
	while(dinner_is_on(info))
	{
		while (i < info->philo_num)
			check_death(info->philos[i++]);
		check_dinner_state(info);		
		i = 0;
		usleep(20);
	}
	return (NULL);
}

void	check_death(t_philo *philo)
{
	struct timeval	current_time;
	long	time_diff;

	pthread_mutex_lock(&philo->data_access);
	if (philo->finished == false)
	{
		gettimeofday(&current_time, NULL);
		time_diff = get_time_diff(philo->last_eat_time, current_time);
		if (time_diff > philo->info->time_to_die)
		{
			philo->info->all_alive = false;
			print_out(philo, "has died of starvation");
		}
	}
	pthread_mutex_unlock(&philo->data_access);

}

void	check_dinner_state(t_info *info)
{
	int		i;
	bool	finished;

	i = 0;
	finished = true;
	while (i < info->philo_num)
	{
		pthread_mutex_lock(&info->philos[i]->data_access);
		if (info->philos[i]->finished == false)
			finished = false;
		pthread_mutex_unlock(&info->philos[i]->data_access);
		i++;
	}
	info->all_finished = finished;
}

void	*init_waiter(void *args)
{
	t_info	*info;
	int		i;

	i = 0;
	info = (t_info *)args;
	while(dinner_is_on(info))
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
		if(i == info->philo_num)
			return ;
	}
}