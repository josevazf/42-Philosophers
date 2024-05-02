/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:21:06 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/05/02 09:17:54 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* Spinlock to synchronize all threads */
void	await_philos(t_dinner *dinner, t_philo *philo)
{
	while (!get_bool(&dinner->dinner_mutex, &dinner->philos_ready))
		;
	usleep(10000 + (philo->index % 2) * 200);
	(void)philo;
}

/* Desyncs to force sleep when philo nb is odd and tt_eat equals tt_sleep */
void	desync_philos(t_philo *philo)
{
	if (philo->dinner->nb_philos % 2)
	{
		if (philo->index % 2)
			usleep_redux(philo->dinner->tt_eat / 2, philo->dinner);
	}
	else
	{
		if (philo->index % 2)
			think_action(philo, false);
	}
}

/* Process a single philo */
void	*process_single_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	await_philos(philo->dinner, philo);
	increase_long(&philo->dinner->dinner_mutex, \
		&philo->dinner->nb_threads_running);
	print_fork(1, philo);
	while (!sim_finished(philo->dinner))
		usleep_redux(100, philo->dinner);
	return (NULL);
}

/* Begin dinner simulation */
void	*dinner_sim(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	await_philos(philo->dinner, philo);
	set_long(&philo->philo_mutex, &philo->last_meal_time, get_current_time());
	increase_long(&philo->dinner->dinner_mutex, \
		&philo->dinner->nb_threads_running);
	desync_philos(philo);
	while (!sim_finished(philo->dinner))
	{
		if (!get_bool(&philo->philo_mutex, &philo->hungry))
			break ;
		eat_action(philo);
		print_sleeping(philo);
		usleep_redux(philo->dinner->tt_sleep, philo->dinner);
		think_action(philo, true);
	}
	return (NULL);
}

/* Create all threads and synchronize to start all threads at the same time */
void	start_dinner(t_dinner *dinner)
{
	int	i;

	i = -1;
	if (dinner->nb_meals == 0)
		return ;
	else if (dinner->nb_philos == 1)
		pthread_create(&dinner->philos[0].thread_index, NULL, \
			process_single_philo, &dinner->philos[0]);
	else
	{
		while (++i < dinner->nb_philos)
		{
			pthread_create(&dinner->philos[i].thread_index, NULL, \
				dinner_sim, &dinner->philos[i]);
		}
	}
	pthread_create(&dinner->death_monitor, NULL, death_checker, dinner);
	set_long(&dinner->dinner_mutex, &dinner->start_time, \
		get_current_time() + 10);
	set_bool(&dinner->dinner_mutex, &dinner->philos_ready, true);
	i = -1;
	while (++i < dinner->nb_philos)
		pthread_join(dinner->philos[i].thread_index, NULL);
	set_bool(&dinner->dinner_mutex, &dinner->finished, true);
	pthread_join(dinner->death_monitor, NULL);
}
