/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philisophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 21:41:32 by lbastien          #+#    #+#             */
/*   Updated: 2023/11/30 21:41:35 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "../libft/include/libft.h"
#include <pthread.h>

//Enum for Philo state
typedef enum s_state
{
	EATING,
	SLEEPING,
	THINKING
}	t_state;

typedef struct s_info
{
	t_philo	**philos;
	int		philo_num;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		target_eat;
} t_info;

typedef struct s_philo
{
	int		id;
	t_state	state;
	bool	finished;
	pthread_t thread;
} t_philo;

int		ft_check_input(int argc, char **argv);
t_info	*init_info(int argc, char **argv);
void	ft_exit(char *error);

#endif