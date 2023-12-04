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
# include "../include/philisophers.h"

t_info	*init_info(int argc, char **argv, struct timeval start_time)
{
	t_info *info;

	info = (t_info *)malloc(sizeof(t_info));
	info->philos = NULL;
	info->philo_num = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		info->target_eat = ft_atoi(argv[5]);
		ft_printf("target_eat setup to %d\n", info->target_eat);
	}
	else
	{
		info->target_eat = 0;
	}
	info->dead = false;
	info->all_finished = false;
	pthread_mutex_init(&info->print, NULL);
	info->start_time = start_time;
	return (info);
}

void	init_mutexes(t_info *info)
{
	int i;

	i = 0;
	info->forks = malloc(sizeof(pthread_mutex_t) * info->philo_num);
	if(!info->forks)
		ft_exit(info, "Error allocating memory for the mutex array");
	while (i < info->philo_num)
		pthread_mutex_init(&info->forks[i++], NULL);
}

t_philo **init_philos_array(t_info *info)
{
	t_philo **philos;
	int	i;

	i = 0;
	philos = (t_philo **)malloc(sizeof(t_philo) * info->philo_num);
	if (!philos)
		ft_exit(info, "Error allocating memory for the philos struct array");
	while (i < info->philo_num)
	{
		philos[i] = init_philo(info, i);
		i++;
	}
	return (philos);
}

t_philo *init_philo(t_info *info, int i)
{
	t_philo 	*philo;
	int			return_value;
	struct timeval	current_time;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		ft_exit(info, "Error allocating memory for philo");
	philo->id = i;
	philo->l_fork = &info->forks[i];
	philo->r_fork = &info->forks[(i + 1) % info->philo_num];
	philo->info = info;
	philo->finished = false;
	philo->eat_count = 0;
	print_out(philo, "initiated");
	return_value = pthread_create(&philo->thread, NULL, routine, (void *) philo);
	if (return_value)
		ft_exit(info, "Error creating the thread for philo");
	gettimeofday(&current_time, NULL);
	philo->last_eat_time = current_time;
	return(philo);
}

void	init_workers(t_info *info)
{
	int	return_value;

	return_value = pthread_create(&info->monitor, NULL, init_monitor, (void *) info);
	if (return_value)
		ft_exit(info, "Error creating the thread for philo");
}