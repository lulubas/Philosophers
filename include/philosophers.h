/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
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
# include <pthread.h>
# include <sys/time.h>

//Enum for Philo state
typedef enum s_state
{
	EATING,
	SLEEPING,
	THINKING
}	t_state;

typedef struct s_info	t_info;
typedef struct s_philo
{
	int				id;
	int				index;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	data_access;
	t_info			*info;
	struct timeval	last_eat_time;
	long			time_diff;
	int				eat_count;
	bool			can_eat;
	bool			next_round;
	bool			finished;
	bool			dead;
	pthread_t		thread;

}	t_philo;

typedef struct s_info
{
	t_philo			**philos;
	pthread_mutex_t	*forks;
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				target_eat;
	bool			all_finished;
	bool			all_alive;
	pthread_mutex_t	print;
	pthread_t		monitor;
	pthread_t		waiter;
	struct timeval	start_time;
}	t_info;

int		ft_check_input(int argc, char **argv);

//INIT DATA STRUCTURES AND THREAD
t_info	*init_info_struct(int argc, char **argv);
void	init_forks_mutex(t_info *info);
t_philo	**init_philos_array(t_info *info);
t_philo	*init_philo_struct(t_info *info, int num);
void	init_workers(t_info *info);

//WORKERS
void	*monitor_thread(void *args);
void	check_death(t_philo *philo);
void	check_dinner_state(t_info *info);
void	*waiter_thread(void *args);
bool	check_can_eat(t_philo *philo);
void	wait_for_next_round(t_info *info);

//ACTIONS
void	*routine(void *arg);
void	to_think(t_philo *philo);
void	pick_up_forks(t_philo *philo);
void	to_eat(t_philo *philo);
void	put_down_forks(t_philo *philo);
void	to_sleep(t_philo *philo);

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
int		dinner_is_on(t_info *info);

#endif