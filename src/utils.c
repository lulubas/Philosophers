/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 16:01:25 by lbastien          #+#    #+#             */
/*   Updated: 2023/12/02 16:01:27 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/philisophers.h"

void	print_out(t_philo *philo, char *str)
{
	struct timeval current_time;
    long milliseconds;
	
	gettimeofday(&current_time, NULL);
    milliseconds = (current_time.tv_sec - philo->info->start_time.tv_sec) * 1000;
    milliseconds += (current_time.tv_usec - philo->info->start_time.tv_usec) / 1000;
	pthread_mutex_lock(&philo->info->print);
	ft_printf("[%dms] %d %s\n", milliseconds, philo->id, str);
	pthread_mutex_unlock(&philo->info->print);
}