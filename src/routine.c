/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 13:01:11 by lbastien          #+#    #+#             */
/*   Updated: 2023/12/02 13:01:14 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
# include "../include/philisophers.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->finished == false && dinner_is_on(philo->info))
	{
		while (philo->next_round == false && dinner_is_on(philo->info))
			usleep(20);
		to_think(philo);
		if (philo->can_eat == true)
		{
			pick_up_forks(philo);
			to_eat(philo);
			put_down_forks(philo);
			if (philo->info->target_eat)
			{
				if(philo->eat_count == philo->info->target_eat)
					philo->finished = true;
			}
		philo->next_round = false;
		to_sleep(philo);
		}
		philo->next_round = false;
	}
	return (NULL);
}

void	to_think(t_philo *philo)
{
	print_out(philo, "is thinking");
}

void	to_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data_access);
	if(philo->can_eat == true && dinner_is_on(philo->info))
	{
		gettimeofday(&philo->last_eat_time, NULL);
		print_out(philo, "is eating");
		philo->eat_count++;
		usleep(1000 * philo->info->time_to_eat);
	}
	pthread_mutex_unlock(&philo->data_access);
}

void	to_sleep(t_philo *philo)
{
	print_out(philo, "is sleeping");
	usleep(1000 * philo->info->time_to_sleep);
}

void	pick_up_forks(t_philo *philo)
{
	if (philo->id == philo->info->philo_num - 1)
	{
		pthread_mutex_lock(philo->r_fork);
		print_out(philo, "has taken a fork (r)");
		pthread_mutex_lock(philo->l_fork);
		print_out(philo, "has taken a fork (l)");
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		print_out(philo, "has taken a fork (l)");
		pthread_mutex_lock(philo->r_fork);
		print_out(philo, "has taken a fork (r)");
	}
}

void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	print_out(philo, "has put down a fork (l)");
	if (philo->info->philo_num > 1)
	{
		pthread_mutex_unlock(philo->r_fork);
		print_out(philo, "has put down a fork (r)");
	}
}