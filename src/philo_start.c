/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:21:06 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/04/29 10:56:41 by jrocha-v         ###   ########.fr       */
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
	set_long(&philo->philo_mutex, &philo->last_meal_time, get_current_time());
	philo->meal_count++;
	print_action(EATING, philo);
	usleep_redux(philo->dinner->tt_eat, philo->dinner);
	if (philo->dinner->nb_meals > 0 && \
		philo->meal_count == philo->dinner->nb_meals)
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
	philo->last_meal_time = get_current_time();
}

/*  */
void	*dinner_sim(void *data)
{
	t_philo	*philo;
	
	philo = (t_philo *)data;
	await_philos(philo->dinner, philo);
	increase_long(&philo->dinner->dinner_mutex, \
		&philo->dinner->nb_threads_running);
	while (!sim_finished(philo->dinner))
	{
		if (!get_bool(&philo->philo_mutex, &philo->hungry))
			break ;
		eat_action(philo);
		print_action(SLEEPING, philo);
		usleep_redux(philo->dinner->tt_sleep, philo->dinner);
		think_action(philo);
	}
	return (NULL); 
}

void	*process_single_philo(void *data)
{
	t_philo *philo;
	
	philo = (t_philo *)data;
	await_philos(philo->dinner, philo);
	increase_long(&philo->dinner->dinner_mutex, \
		&philo->dinner->nb_threads_running);
	print_action(TAKE_FIRST_FORK, philo);
	while (!sim_finished(philo->dinner))
		usleep_redux(200, philo->dinner);
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
		    safe_thread(&dinner->philos[0].thread_index, process_single_philo, \
        		&dinner->philos[0], CREATE);
	else
	{
		while (++i < dinner->nb_philos)
		{
			safe_thread(&dinner->philos[i].thread_index, dinner_sim, \
				&dinner->philos[i], CREATE);
		}
	}
	safe_thread(&dinner->death_monitor, death_checker, dinner, CREATE);
	dinner->start_time = get_current_time() + 10;
	set_bool(&dinner->dinner_mutex, &dinner->philos_ready, true);
	i = -1;
	while (++i < dinner->nb_philos)
		safe_thread(&dinner->philos[i].thread_index, NULL, NULL, JOIN);
	set_bool(&dinner->dinner_mutex, &dinner->finished, true); // all philos full
	safe_thread(&dinner->death_monitor, NULL, NULL, JOIN);
}
