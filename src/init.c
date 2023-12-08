/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 13:00:57 by lbastien          #+#    #+#             */
/*   Updated: 2023/12/02 13:00:59 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philosophers.h"

t_info	*init_info_struct(int argc, char **argv)
{
	t_info			*info;
	struct timeval	start_time;

	info = (t_info *)malloc(sizeof(t_info));
	info->philos = NULL;
	info->philo_num = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->target_eat = ft_atoi(argv[5]);
	else
		info->target_eat = 0;
	info->all_finished = false;
	info->all_alive = true;
	pthread_mutex_init(&info->print, NULL);
	gettimeofday(&start_time, NULL);
	info->start_time = start_time;
	return (info);
}

void	init_forks_mutex(t_info *info)
{
	int	i;

	i = 0;
	info->forks = malloc(sizeof(pthread_mutex_t) * info->philo_num);
	if (!info->forks)
		ft_exit(info, "Error allocating memory for the mutex array");
	while (i < info->philo_num)
		pthread_mutex_init(&info->forks[i++], NULL);
}

t_philo	**init_philos_array(t_info *info)
{
	t_philo	**philos;
	int		i;

	i = 0;
	philos = (t_philo **)malloc(sizeof(t_philo) * info->philo_num);
	if (!philos)
		ft_exit(info, "Error allocating memory for the philos struct array");
	while (i < info->philo_num)
	{
		philos[i] = init_philo_struct(info, i);
		i++;
	}
	return (philos);
}

t_philo	*init_philo_struct(t_info *info, int i)
{
	t_philo			*philo;
	int				value;
	struct timeval	current_time;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		ft_exit(info, "Error allocating memory for philo");
	philo->id = i;
	philo->index = i;
	philo->l_fork = &info->forks[i];
	philo->r_fork = &info->forks[(i + 1) % info->philo_num];
	pthread_mutex_init(&philo->data_access, NULL);
	philo->info = info;
	gettimeofday(&current_time, NULL);
	philo->last_eat_time = current_time;
	philo->eat_count = 0;
	philo->can_eat = false;
	philo->next_round = false;
	philo->finished = false;
	philo->dead = false;
	value = pthread_create(&philo->thread, NULL, routine, (void *)philo);
	if (value)
		ft_exit(info, "Error creating the thread for philo");
	return (philo);
}

void	init_workers(t_info *info)
{
	int	return_value;

	return_value = pthread_create(&info->monitor, NULL, \
	monitor_thread, (void *) info);
	if (return_value)
		ft_exit(info, "Error creating the thread for philo");
	return_value = pthread_create(&info->waiter, NULL, \
	waiter_thread, (void *) info);
	if (return_value)
		ft_exit(info, "Error creating the thread for philo");
}
