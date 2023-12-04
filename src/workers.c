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
	while(info->dead == false && info->all_finished == false)
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

	if (philo->finished == false)
	{
		pthread_mutex_lock(&philo->state_mutex);
		gettimeofday(&current_time, NULL);
		time_diff = get_time_diff(philo->last_eat_time, current_time);
		if (time_diff > philo->info->time_to_die)
		{
			philo->info->dead = true;
			print_out(philo, "has died of starvation");
		}
		pthread_mutex_unlock(&philo->state_mutex);
	}
}

void	check_dinner_state(t_info *info)
{
	int		i;
	bool	finished;

	i = 0;
	finished = true;
	while (i < info->philo_num)
	{
		pthread_mutex_lock(&info->philos[i]->state_mutex);
		if (info->philos[i]->finished == false)
			finished = false;
		pthread_mutex_unlock(&info->philos[i]->state_mutex);
		i++;
	}
	info->all_finished = finished;
}