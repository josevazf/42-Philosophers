/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:21:06 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/04/16 13:02:00 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	think_action(t_philo *philo)
{
	print_action(THINKING, philo, false);
}

void	eat_action(t_philo *philo)
{
	safe_mutex(&philo->first_fork->fork, LOCK);
	print_action(TAKE_FIRST_FORK, philo, false);
	safe_mutex(&philo->second_fork->fork, LOCK);
	print_action(TAKE_SECOND_FORK, philo, false);
	set_long(&philo->philo_mutex, &philo->last_meal_time, get_current_time(MILISECOND));
	philo->meal_count++;
	print_action(EATING, philo, false);
	usleep_redux(philo->dinner->tt_eat, philo->dinner);
	if (philo->dinner->nb_meals > 0 && philo->meal_count == philo->dinner->nb_meals)
		set_bool(&philo->philo_mutex, &philo->hungry, true);
	safe_mutex(&philo->first_fork->fork, UNLOCK);
	safe_mutex(&philo->second_fork->fork, UNLOCK);
	
}

/* Spinlock to synchronize all threads */
void	await_philos(t_dinner *dinner)
{
	while (!get_bool(&dinner->dinner_mutex, &dinner->philos_ready))
		;
}

/*  */
void	*dinner_sim(void *data)
{
	t_philo	*philo;
	
	philo = (t_philo *)data;
	await_philos(philo->dinner);
	while (!sim_finished(philo->dinner))
	{
		// 1 - philo full?
		if (!philo->hungry)
			break ;
		// 2 - philo eats
		eat_action(philo);
		// 3 - philo sleeps
		print_action(SLEEPING, philo, false);
		usleep_redux(philo->dinner->tt_sleep, philo->dinner);
		// 4 - philo thinks
		think_action(philo);
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
/* 	else if (dinner->nb_philos == 1)
		process_one_philo(&dinner); // to do */
	else
	{
		while (++i < dinner->nb_philos)
		{
			safe_thread(&dinner->philos[i].thread_index, dinner_sim, \
				&dinner->philos[i], CREATE);
		}
	}
	dinner->start_time = get_current_time(MILISECOND);
	set_bool(&dinner->dinner_mutex, &dinner->philos_ready, true);
	i = -1;
	while (++i < dinner->nb_philos)
		safe_thread(&dinner->philos[i].thread_index, NULL, NULL, JOIN);
}
