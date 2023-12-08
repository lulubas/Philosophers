/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 21:17:02 by lbastien          #+#    #+#             */
/*   Updated: 2023/11/30 21:17:10 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philosophers.h"

int	main(int argc, char **argv)
{
	int		check;
	t_info	*info;
	t_philo	**philos;
	int		return_value;

	info = NULL;
	philos = NULL;
	check = ft_check_input(argc, argv);
	if (!check)
		ft_exit(info, "Arguments are incorrect");
	info = init_info_struct(argc, argv);
	init_forks_mutex(info);
	info->philos = init_philos_array(info);
	init_workers(info);
	return_value = pthread_join(info->monitor, NULL);
	if (return_value)
		ft_printf("Failed to join monitor thread\n");
	return_value = pthread_join(info->waiter, NULL);
	if (return_value)
		ft_printf("Failed to join waiter thread\n");
	if (info->all_alive == false)
		ft_exit(info, "One philosopher died :(. End of dinner.");
	if (info->all_finished == true)
		ft_exit(info, "Philosophers have completed their meal :)");
	return (1);
}

int	ft_check_input(int argc, char **argv)
{
	int	i;
	int	j;
	int	philo_num;

	i = 1;
	j = 0;
	if (argc < 5 || argc > 6)
		return (0);
	while (i < argc)
	{
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (0);
			j++;
		}
		if (ft_atoi(argv[i]) < 1)
			return (0);
		j = 0;
		i++;
	}
	philo_num = ft_atoi(argv[1]);
	if (philo_num > 200)
		return (0);
	return (1);
}

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
				if (philo->eat_count == philo->info->target_eat)
					philo->finished = true;
			}
			philo->next_round = false;
			to_sleep(philo);
		}
		philo->next_round = false;
	}
	return (NULL);
}
