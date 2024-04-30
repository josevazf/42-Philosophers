/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_printer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:53:17 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/04/30 15:51:18 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* Print taking fork action */
void	print_fork(int fork, t_philo *philo)
{
	long	t_elapsed;

	if (philo->hungry == false)
		return ;
	pthread_mutex_lock(&philo->dinner->print_mutex);
	t_elapsed = get_current_time() - philo->dinner->start_time;
	if ((fork == 1 || fork == 2) \
		&& !sim_finished(philo->dinner))
		printf("%ld %d has taken a fork\n", t_elapsed, philo->index);
	pthread_mutex_unlock(&philo->dinner->print_mutex);
}

/* Print eating action */
void	print_eating(t_philo *philo)
{
	long	t_elapsed;

	if (philo->hungry == false)
		return ;
	pthread_mutex_lock(&philo->dinner->print_mutex);
	t_elapsed = get_current_time() - philo->dinner->start_time;
	if (!sim_finished(philo->dinner))
		printf("%ld %d is eating\n", t_elapsed, philo->index);
	pthread_mutex_unlock(&philo->dinner->print_mutex);
}

/* Print sleeping action */
void	print_sleeping(t_philo *philo)
{
	long	t_elapsed;

	if (philo->hungry == false)
		return ;
	pthread_mutex_lock(&philo->dinner->print_mutex);
	t_elapsed = get_current_time() - philo->dinner->start_time;
	if (!sim_finished(philo->dinner))
		printf("%ld %d is sleeping\n", t_elapsed, philo->index);
	pthread_mutex_unlock(&philo->dinner->print_mutex);
}

/* Print thinking action */
void	print_thinking(t_philo *philo)
{
	long	t_elapsed;

	if (philo->hungry == false)
		return ;
	pthread_mutex_lock(&philo->dinner->print_mutex);
	t_elapsed = get_current_time() - philo->dinner->start_time;
	if (!sim_finished(philo->dinner))
		printf("%ld %d is thinking\n", t_elapsed, philo->index);
	pthread_mutex_unlock(&philo->dinner->print_mutex);
}

/* Print dying action */
void	print_died(t_philo *philo)
{
	long	t_elapsed;

	if (philo->hungry == false)
		return ;
	pthread_mutex_lock(&philo->dinner->print_mutex);
	t_elapsed = get_current_time() - philo->dinner->start_time;
	printf("%ld %d died\n", t_elapsed, philo->index);
	pthread_mutex_unlock(&philo->dinner->print_mutex);
}
