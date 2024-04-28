/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:56:38 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/04/28 19:29:24 by jrocha-v         ###   ########.fr       */
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

	i = -1;
	while (++i < dinner->nb_philos)
	{
		dinner->philos[i].index = i + 1;
		dinner->philos[i].hungry = true;
		dinner->philos[i].meal_count = 0;
		dinner->philos[i].dinner = dinner;
		safe_mutex(&dinner->philos[i].philo_mutex, INIT);
		set_forks(&dinner->philos[i], dinner->forks, i);
	}
}

void	setup_dinner(t_dinner *dinner)
{
	int	i;

	i = -1;
	dinner->finished = false;
	dinner->philos_ready = false;
	dinner->nb_threads_running = 0;
	safe_mutex(&dinner->dinner_mutex, INIT);
	safe_mutex(&dinner->print_mutex, INIT);
	dinner->philos = safe_malloc(sizeof(t_philo) * dinner->nb_philos);
	dinner->forks = safe_malloc(sizeof(t_fork) * dinner->nb_philos);
	philos_init(dinner);
	while (++i < dinner->nb_philos)
	{
		safe_mutex(&dinner->forks[i].fork, INIT);
		dinner->forks[i].fork_index = i;
	}
}
