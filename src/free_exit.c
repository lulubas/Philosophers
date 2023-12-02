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
# include "../include/philisophers.h"

void	ft_exit(t_info *info, char *error)
{
	if (info)
	{
		if (info->philos)
		{
			join_threads(info);
			free_philos(info);
		}
		if (info->forks)
			free_forks(info);
		free (info);
	}
	pthread_mutex_destroy(&info->print);
	ft_printf("%s\n", error);
	exit (0);
}

void	join_threads(t_info *info)
{
	int	i;
	int	return_value;

	i = 0;
	while (i < info->philo_num)
		return_value = pthread_join(info->philos[i++]->thread, NULL);
}


void free_philos(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->philo_num)
		free(info->philos[i++]);
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