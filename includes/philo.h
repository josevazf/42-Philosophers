/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:47:59 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/05/02 09:39:52 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <limits.h>
# include <stdbool.h>
# include <sys/time.h>
# include <errno.h>

# define ERROR 1
# define SUCCESS 0

typedef pthread_mutex_t	t_mutex;

typedef struct s_dinner	t_dinner;

typedef struct s_fork
{
	t_mutex			fork;
	int				fork_index;
}						t_fork;

typedef struct s_philo
{
	int				index;
	bool			hungry;
	long			meal_count;
	long			last_meal_time;
	t_fork			*first_fork;
	t_fork			*second_fork;
	t_mutex			philo_mutex;
	pthread_t		thread_index;
	t_dinner		*dinner;
}						t_philo;

typedef struct s_dinner
{
	long			nb_philos;
	long			start_time;
	long			tt_die;
	long			tt_eat;
	long			tt_sleep;
	long			nb_meals;
	long			nb_threads_running;
	bool			philos_ready;
	bool			finished;
	t_mutex			dinner_mutex;
	t_mutex			print_mutex;
	pthread_t		death_monitor;
	t_fork			*forks;
	t_philo			*philos;
}						t_dinner;

// philo_main.c

// philo_input.c
int		ft_isdigit(int c);
long	ft_atol_redux(const char *nstr);
void	check_input(t_dinner *dinner, char **argv);

// philo_setup.c
void	set_forks(t_philo *philo, t_fork *forks, int i);
void	philos_init(t_dinner *dinner);
void	setup_dinner(t_dinner *dinner);

// philo_start.c
void	await_philos(t_dinner *dinner, t_philo *philo);
void	desync_philos(t_philo *philo);
void	*process_single_philo(void *data);
void	*dinner_sim(void *data);
void	start_dinner(t_dinner *dinner);

// philo_actions.c
void	think_action(t_philo *philo, bool sim_started);
void	eat_action(t_philo *philo);

// philo_printer.c
void	print_fork(int fork, t_philo *philo);
void	print_eating(t_philo *philo);
void	print_sleeping(t_philo *philo);
void	print_thinking(t_philo *philo);
void	print_died(t_philo *philo);

// philo_get_set.c
void	set_bool(t_mutex *mutex, bool *dest, bool value);
bool	get_bool(t_mutex *mutex, bool *value);
void	set_long(t_mutex *mutex, long *dest, long value);
long	get_long(t_mutex *mutex, long *value);
long	increase_long(t_mutex *mutex, long *value);

//philo_monitor.c
bool	philo_died(t_philo *philo);
bool	sim_finished(t_dinner *dinner);
bool	threads_ready(t_mutex *mutex, long *threads, long nbr_philo);
void	*death_checker(void *data);

// philo_utils.c
void	usleep_redux(long sleep_t, t_dinner *dinner);
long	get_current_time(void);
void	cleanup(t_dinner *dinner);

// philo_errors.c
void	*safe_malloc(size_t bytes);
int		args_error(void);
int		exit_error(const char *str);

#endif
