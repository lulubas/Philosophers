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
	int check;
	t_info	*info;
	t_philo	**philos;

	info = NULL;
	philos = NULL;
	check = ft_check_input(argc, argv);
	if (!check)
		ft_exit(info, "Arguments are incorrect");
	info = init_info(argc, argv);
	init_mutexes(info);
	info->philos = init_philos_array(info);
	ft_exit(info, "End of main reached");
	return (1);
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
t_info	*init_info(int argc, char **argv)
{
	t_info *info;

	info = (t_info *)malloc(sizeof(t_info));
	info->philos = NULL;
	info->philo_num = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->target_eat = ft_atoi(argv[5]);
	return(info);
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
		usleep(200000);
		i++;
	}
	return (philos);
}

t_philo *init_philo(t_info *info, int i)
{
	t_philo 	*philo;
	int			return_value;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		ft_exit(info, "Error allocating memory for philo");
	philo->id = i;
	philo->state = THINKING;
	philo->l_fork = &info->forks[i];
	philo->r_fork = &info->forks[(i + 1) % info->philo_num];
	philo->finished = false;
	return_value = pthread_create(&philo->thread, NULL, routine, (void *) philo);
	if (return_value)
		ft_exit(info, "Error creating the thread for philo");
	return(philo);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	philo = (t_philo *)arg;
	return NULL;
}

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
