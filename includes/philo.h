/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:47:59 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/02/21 18:00:14 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>

# define ERROR 1
# define SUCCESS 0

typedef struct s_table
{
	int				nb_philos;
	int				nb_eat;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	struct	s_philo	philos;
}	t_table;

typedef struct s_philo
{
	int				index;
	struct s_philo	*prev;
	struct s_philo	*next;
}	t_philo;

// main.c

#endif
