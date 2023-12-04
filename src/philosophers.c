/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philisophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 21:17:02 by lbastien          #+#    #+#             */
/*   Updated: 2023/11/30 21:17:10 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/philisophers.h"

int main(int argc, char **argv)
{
	int 			check;
	t_info			*info;
	t_philo			**philos;
	struct timeval	start_time;
	int				return_value;

	info = NULL;
	philos = NULL;
	check = ft_check_input(argc, argv);
	if (!check)
		ft_exit(info, "Arguments are incorrect");
	gettimeofday(&start_time, NULL);
	info = init_info(argc, argv, start_time);
	init_mutexes(info);
	info->philos = init_philos_array(info);
	init_workers(info);
	return_value = pthread_join(info->monitor, NULL);
	if (return_value)
		ft_printf("Failed to join monitor thread\n");
	if (info->dead == true)
		ft_exit(info, "One philosopher died :(. End of dinner.");
	if (info->all_finished == true)
		ft_exit(info, "All philosophers have completed their meal :) End of dinner.");
	return (1);
}

int	ft_check_input(int argc, char **argv)
{
	int	i;
	int j;

	i = 1;
	j = 0;
	if (argc < 5 || argc > 6)
		return (0);
	while (i < argc)
	{
		while (argv[i][j])
		{
			if(!ft_isdigit(argv[i][j]))
				return(0);
			j++;
		}
		if (ft_atoi(argv[i]) < 1)
			return(0);
		j = 0;
		i++;
	}
	return (1);
}