/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:47:59 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/03/26 17:16:13 by jrocha-v         ###   ########.fr       */
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

# define ERROR 1
# define SUCCESS 0

# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define DEAD 666

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
	int				nb_philos;
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


// philo_utils.c
long	get_current_time(void);

// philo_errors.c
int		args_error(void);
int		pth_check(int pthread_ret);


#endif
