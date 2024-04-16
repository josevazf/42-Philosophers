/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:56:38 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/04/16 13:13:00 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	set_forks(t_philo *philo, t_fork *forks, int i)
{
	if (philo->index % 2 == 0)
	{
		philo->first_fork = &forks[i];
		philo->second_fork = &forks[(i + 1) % philo->dinner->nb_philos];	
	}
	else
	{
		philo->first_fork = &forks[(i + 1) % philo->dinner->nb_philos];	
		philo->second_fork = &forks[i];
	}
}

void	philos_init(t_dinner *dinner)
{
	int	i;
	t_philo	*philo;

	i = -1;
	while (++i < dinner->nb_meals)
	{
		philo = philo + i;
		philo->index = i + 1;
		philo->hungry = false;
		philo->meal_count = 0;
		philo->dinner = dinner;
		safe_mutex(&philo->philo_mutex, INIT);
		set_forks(philo, dinner->forks, i);
	}
}

void	setup_dinner(t_dinner *dinner)
{
	int	i;

	i = -1;
	dinner->finished = false;
	dinner->philos_ready = false;
	safe_mutex(&dinner->dinner_mutex, INIT);
	safe_mutex(&dinner->print_mutex, INIT);
	dinner->philos = safe_malloc(sizeof(t_philo) * dinner->nb_philos);
	dinner->forks = safe_malloc(sizeof(t_fork) * dinner->nb_philos);
	while (++i < dinner->nb_philos)
	{
		safe_mutex(&dinner->forks[i].fork, INIT);
		dinner->forks[i].fork_index = i;
	}
}
