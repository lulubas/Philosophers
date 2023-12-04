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

#include "../libft/include/libft.h"
#include <pthread.h>
#include <sys/time.h>

//Enum for Philo state
typedef enum s_state
{
	EATING,
	SLEEPING,
	THINKING
}	t_state;

typedef struct s_info t_info;
typedef struct s_philo
{
	int				id;
	int				eat_count;
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	state_mutex;
	t_info			*info;
	struct timeval 	last_eat_time;
	long			time_diff;
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
	bool			all_finished;
	pthread_mutex_t print;
	pthread_t		monitor;
	struct timeval 	start_time;
} t_info;

int		ft_check_input(int argc, char **argv);

//INIT
t_info	*init_info(int argc, char **argv, struct timeval start_time);
void	init_mutexes(t_info *info);
t_philo **init_philos_array(t_info *info);
t_philo *init_philo(t_info *info, int num);
void	init_workers(t_info *info);
void	*init_monitor(void *args);

//WORKERS
void	check_death(t_philo *philo);
void	check_dinner_state(t_info *info);

//ACTIONS
void 	*routine(void *arg);
void	to_think(t_philo *philo);
void	to_eat(t_philo *philo);
void	to_sleep(t_philo *philo);
void	pick_up_forks(t_philo *philo);
void	put_down_forks(t_philo *philo);

//EXIT
void	ft_exit(t_info *info, char *error);
void	join_threads(t_info *info);
void	free_philos(t_info *info);
void	free_forks(t_info *info);

//UTILS
void	print_out(t_philo *philo, char const *str, ...);
void	print_state(t_info *info);
long	get_time(struct timeval time);
long	get_time_diff(struct timeval start, struct timeval end);

#endif