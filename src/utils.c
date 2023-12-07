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

void	print_out(t_philo *philo, const char *str, ...)
{
	struct timeval current_time;
	long timestamp;
	va_list	args;

	gettimeofday(&current_time, NULL);
	timestamp = get_time(current_time) - get_time(philo->info->start_time);
	pthread_mutex_lock(&philo->info->print);
	printf("[%ldms] %d ", timestamp, philo->id);
	va_start(args, str);
	vprintf(str, args);
	va_end(args);
	printf("\n");
	pthread_mutex_unlock(&philo->info->print);
}

void	print_state(t_info *info)
{
	int	i;

	i = 0;
	ft_printf("=====\n");
	while(i < info->philo_num)
	{
		ft_printf("Philo %d ate %d time(s)\n", i, info->philos[i]->eat_count);
		i++;
	}
	ft_printf("=====\n");
}

long	get_time(struct timeval time)
{
	long	milliseconds;

	milliseconds = time.tv_sec * 1000;
	milliseconds += time.tv_usec / 1000;
	return (milliseconds);
}

long	get_time_diff(struct timeval start, struct timeval end)
{
	long	time_diff;
	time_diff = get_time(end) - get_time(start);
	return (time_diff);
}

int		dinner_is_on(t_info *info)
{
	if (info->all_alive == true && info->all_finished == false)
		return (1);
	else	
		return(0);
}