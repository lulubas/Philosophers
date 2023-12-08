/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 13:03:15 by lbastien          #+#    #+#             */
/*   Updated: 2023/12/02 13:03:17 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philosophers.h"

void	ft_exit(t_info *info, char *error)
{
	if (info)
	{
		if (info->philos)
		{
			join_threads(info);
			print_state(info);
			free_philos(info);
		}
		if (info->forks)
			free_forks(info);
		pthread_mutex_destroy(&info->print);
		free (info);
	}
	ft_printf("%s\n", error);
	exit (0);
}

void	join_threads(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->philo_num)
	{
		pthread_join(info->philos[i]->thread, NULL);
		pthread_mutex_destroy(&info->philos[i]->data_access);
		i++;
	}
}

void	free_philos(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->philo_num)
		free (info->philos[i++]);
	free (info->philos);
}

void	free_forks(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->philo_num)
		pthread_mutex_destroy(&info->forks[i++]);
	free(info->forks);
}
