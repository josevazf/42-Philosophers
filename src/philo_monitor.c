/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:16:48 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/04/28 22:26:02 by jrocha-v         ###   ########.fr       */
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

bool	threads_ready(t_mutex *mutex, long *threads, long nbr_philo)
{
	bool res;

	res = false;
	safe_mutex(mutex, LOCK);
	if (*threads == nbr_philo)
		res = true;
	safe_mutex(mutex, UNLOCK);
	return (res);
}

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
		while (++i < dinner->nb_philos)
		{
			if (philo_died(&dinner->philos[i]))
			{
				set_bool(&dinner->dinner_mutex, &dinner->finished, true);
				print_action(DIED, &dinner->philos[i]);
			}
		}
	}
	return (NULL);
}
