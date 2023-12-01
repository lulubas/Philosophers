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

	check = ft_check_input(argc, argv);
	if (!check)
		ft_exit("Arguments are incorrect");
	info = init_info(argc, argv);
	philos = init_philos_array(info);

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

	int	i = 0;
	philos = (t_philo **)malloc(sizeof(t_philo) * info->philo_num);
	while (i < info->philo_num)
	{
		philos[i] = init_philo(i);
		i++;
	}
}

t_philo *init_philo(int num)
{
	t_philo *philo;
	
	philo = (t_philo *)malloc(sizeof(t_philo));
	philo->id = num;
	philo->state = THINKING;
	philo->finished = false;
	return(philo);
}

void ft_exit(char *error)
{
	ft_printf("%s\n", error);
	exit (0);
}
