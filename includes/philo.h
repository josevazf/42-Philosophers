/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:47:59 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/04/15 15:34:05 by jrocha-v         ###   ########.fr       */
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

typedef struct s_table	t_table;

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
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_t		thread_index;
	t_table			*table;
}	t_philo;

typedef struct s_table
{
	long			nb_philos;
	long			start_time; // ms
	long			tt_die;
	long			tt_eat;
	long			tt_sleep;
	long			nb_meals;
	bool			finished;
	t_fork			*forks; // array to store forks
	t_philo			*philos; // array to store philos
}	t_table;

// philo_main.c


// philo_input.c
int		ft_isdigit(int c);
long	ft_atol_redux(const char *nstr);
void	check_input(t_table *table, char **argv);

// philo_utils.c
long	get_current_time(void);

// philo_handlers.c
void	handle_safe_mutex(int status, t_opcode opcode);
void	safe_mutex(t_mutex *mutex, t_opcode opcode);
void	handle_safe_thread(int status, t_opcode opcode);
void	safe_thread(pthread_t *thread, void *(*func)(void *), \
			void *data, t_opcode opcode);

// philo_errors.c
void	*safe_malloc(size_t bytes);
int		args_error(void);
void	exit_error(const char *str);

#endif
