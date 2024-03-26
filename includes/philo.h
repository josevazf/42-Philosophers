/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:47:59 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/03/26 15:26:19 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

# define ERROR 1
# define SUCCESS 0

# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define DEAD 666

typedef struct s_table
{
	long			start_time; // ms
	int				nb_philos;
	int				nb_meals;
	long			tt_die;
	long			tt_eat;
	long			tt_sleep;
	bool			finished;
	struct	s_philo	*philos;
}	t_table;

typedef struct s_fork
{
	int				index;
}	t_fork;

typedef struct s_philo
{
	int				index;
	int				state;
	int				meal_count;
	long			last_meal_time;
	t_fork			left_fork;
	t_fork			right_fork;
}	t_philo;

// philo_main.c


// philo_utils.c
long	get_current_time(void);

// philo_errors.c
int		args_error(void);
int		pth_check(int pthread_ret);


#endif
