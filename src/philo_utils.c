/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:41:39 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/05/02 09:32:18 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* Usleep function adjusted for precision */
void	usleep_redux(long sleep_t, t_dinner *dinner)
{
	long	start_t;

	start_t = get_current_time();
	while (get_current_time() - start_t < sleep_t)
	{
		if (sim_finished(dinner))
			break ;
		usleep(100);
	}
	return ;
}

/* Get current time in miliseconds */
long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/* Cleanup mutexes and memory */
void	cleanup(t_dinner *dinner)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < dinner->nb_philos)
	{
		philo = &dinner->philos[i];
		pthread_mutex_destroy(&philo->philo_mutex);
	}
	pthread_mutex_destroy(&dinner->print_mutex);
	pthread_mutex_destroy(&dinner->dinner_mutex);
	free(dinner->forks);
	free(dinner->philos);
}
