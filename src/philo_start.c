/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:21:06 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/04/27 16:51:22 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	think_action(t_philo *philo)
{
	print_action(THINKING, philo);
}

void	eat_action(t_philo *philo)
{
	safe_mutex(&philo->first_fork->fork, LOCK);
	print_action(TAKE_FIRST_FORK, philo);
	safe_mutex(&philo->second_fork->fork, LOCK);
	print_action(TAKE_SECOND_FORK, philo);
	set_long(&philo->philo_mutex, &philo->last_meal_time, get_current_time(MILISECOND));
	philo->meal_count++;
	print_action(EATING, philo);
	usleep_redux(philo->dinner->tt_eat, philo->dinner);
	if (philo->dinner->nb_meals > 0 && philo->meal_count == philo->dinner->nb_meals)
		set_bool(&philo->philo_mutex, &philo->hungry, false);
	safe_mutex(&philo->first_fork->fork, UNLOCK);
	safe_mutex(&philo->second_fork->fork, UNLOCK);
}

/* Spinlock to synchronize all threads */
void	await_philos(t_dinner *dinner, t_philo *philo)
{
	while (!get_bool(&dinner->dinner_mutex, &dinner->philos_ready))
		;
	usleep_redux(10 + (philo->index % 2) * 20, dinner);
	philo->last_meal_time = get_current_time(MILISECOND);
}

/*  */
void	*dinner_sim(void *data)
{
	t_philo	*philo;
	
	philo = (t_philo *)data;
	await_philos(philo->dinner, philo);
	while (!sim_finished(philo->dinner))
	{
		// 1 - philo full?
		if (!philo->hungry)
			break ;
		// 2 - philo eats
		eat_action(philo);
		// 3 - philo sleeps
		print_action(SLEEPING, philo);
		usleep_redux(philo->dinner->tt_sleep, philo->dinner);
		// 4 - philo thinks
		think_action(philo);
	}
	return (NULL); 
}

void	death_checker(void *data)
{
	t_dinner *dinner;

	dinner = (t_dinner *)data;
		


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
	safe_thread(&dinner->death_monitor, death_checker, dinner, CREATE);
	
	dinner->start_time = get_current_time(MILISECOND) + 10;
	set_bool(&dinner->dinner_mutex, &dinner->philos_ready, true);
	i = -1;
	while (++i < dinner->nb_philos)
		safe_thread(&dinner->philos[i].thread_index, NULL, NULL, JOIN);
}
