/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:47:59 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/03/24 18:24:18 by jrocha-v         ###   ########.fr       */
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
	int				start_time;
	int				nb_philos;
	int				nb_meals;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	struct	s_philo	*philos;
}	t_table;

typedef struct s_philo
{
	int				index;
	int				state;
	bool			left_f;
	bool			right_f;
	struct s_philo	*prev;
	struct s_philo	*next;
}	t_philo;

// philo_main.c

// philo_errors.c
int		args_error(void);

#endif
