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

typedef struct s_philo
{
	int				id;
	t_state			state;
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	bool			finished;
} t_philo;

typedef struct s_info
{
	t_philo			**philos;
	pthread_mutex_t *forks;
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				target_eat;
	bool			dead;
} t_info;

int		ft_check_input(int argc, char **argv);
t_info	*init_info(int argc, char **argv);
void	init_mutexes(t_info *info);
t_philo **init_philos_array(t_info *info);
t_philo *init_philo(t_info *info, int num);
void 	*routine(void *arg);
void	ft_exit(t_info *info, char *error);
void	join_threads(t_info *info);
void	free_philos(t_info *info);
void	free_forks(t_info *info);


#endif