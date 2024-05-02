/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:16:48 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/05/02 09:30:48 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	tt_die;

	if (!get_bool(&philo->philo_mutex, &philo->hungry))
		return (false);
	elapsed = get_current_time() - get_long(&philo->philo_mutex, \
		&philo->last_meal_time);
	tt_die = philo->dinner->tt_die;
	if (elapsed > tt_die)
		return (true);
	return (false);
}

/* Safe wrapper function to get simulation status */
bool	sim_finished(t_dinner *dinner)
{
	return (get_bool(&dinner->dinner_mutex, &dinner->finished));
}

/* Safe wrapper function to set threads as ready to start dinner */
bool	threads_ready(t_mutex *mutex, long *threads, long nbr_philo)
{
	bool	res;

	res = false;
	pthread_mutex_lock(mutex);
	if (*threads == nbr_philo)
		res = true;
	pthread_mutex_unlock(mutex);
	return (res);
}

/* Safe wrapper function to check for philo death */
void	*death_checker(void *data)
{
	int			i;
	t_dinner	*dinner;

	dinner = (t_dinner *)data;
	while (!threads_ready(&dinner->dinner_mutex, &dinner->nb_threads_running, \
		dinner->nb_philos))
		;
	while (!sim_finished(dinner))
	{
		i = -1;
		while (++i < dinner->nb_philos && !sim_finished(dinner))
		{
			if (philo_died(&dinner->philos[i]))
			{
				set_bool(&dinner->dinner_mutex, &dinner->finished, true);
				print_died(&dinner->philos[i]);
			}
		}
	}
	return (NULL);
}
