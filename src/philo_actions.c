/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 22:27:24 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/04/29 19:07:35 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	think_action(t_philo *philo, bool sim_started)
{
	long	tt_eat;
	long	tt_sleep;
	long	tt_think;

	if (sim_started)
		print_action(THINKING, philo);
	if (philo->dinner->nb_philos % 2 == 0)
		return ;
	else
	{
		tt_eat = philo->dinner->tt_eat;
		tt_sleep = philo->dinner->tt_sleep;
		tt_think = tt_eat * 2 - tt_sleep;
		if (tt_think < 0)
			tt_think = 0;
		usleep_redux(tt_think * 0.5, philo->dinner);
	}
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
