/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:47:59 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/04/16 09:48:26 by jrocha-v         ###   ########.fr       */
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

typedef enum e_opcode
{
	CREATE,
	JOIN,
	DETACH,
	INIT,
	LOCK,
	UNLOCK,
	DESTROY
}			t_opcode;

typedef pthread_mutex_t	t_mutex;

typedef struct s_dinner	t_dinner;

typedef struct s_fork
{
	t_mutex			fork;
	int				fork_index;
}	t_fork;

typedef struct s_philo
{
	int				philo_index;
	bool			hungry; // yes | no
	long			meal_count;
	long			last_meal_time; // ms
	t_fork			*first_fork;
	t_fork			*second_fork;
	pthread_t		thread_index;
	t_dinner			*dinner;
}	t_philo;

typedef struct s_dinner
{
	long			nb_philos;
	long			start_time; // ms
	long			tt_die;
	long			tt_eat;
	long			tt_sleep;
	long			nb_meals;
	bool			philos_ready;
	bool			finished;
	t_mutex			dinner_mutex; // avoid races while reading from table
	t_fork			*forks; // array to store forks
	t_philo			*philos; // array to store philos
}	t_dinner;

// philo_main.c


// philo_input.c
int		ft_isdigit(int c);
long	ft_atol_redux(const char *nstr);
void	check_input(t_dinner *dinner, char **argv);

// philo_setup.c
void	set_forks(t_philo *philo, t_fork *forks, i);
void	philos_init(t_dinner *dinner);
void	setup_dinner(t_dinner *dinner);

// philo_handlers.c
void	handle_safe_mutex(int status, t_opcode opcode);
void	safe_mutex(t_mutex *mutex, t_opcode opcode);
void	handle_safe_thread(int status, t_opcode opcode);
void	safe_thread(pthread_t *thread, void *(*func)(void *), \
			void *data, t_opcode opcode);

// philo_utils.c
long	get_current_time(void);

// philo_errors.c
void	*safe_malloc(size_t bytes);
int		args_error(void);
void	exit_error(const char *str);

#endif
