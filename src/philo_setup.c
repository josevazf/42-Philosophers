/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:56:38 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/04/30 12:25:35 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* Assigns the fork that each philo should take */
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
		dinner->philos[i].last_meal_time = 0;
		dinner->philos[i].dinner = dinner;
		pthread_mutex_init(&dinner->philos[i].philo_mutex, NULL);
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
	pthread_mutex_init(&dinner->dinner_mutex, NULL);
	pthread_mutex_init(&dinner->print_mutex, NULL);
	dinner->philos = safe_malloc(sizeof(t_philo) * dinner->nb_philos);
	dinner->forks = safe_malloc(sizeof(t_fork) * dinner->nb_philos);
	while (++i < dinner->nb_philos)
	{
		pthread_mutex_init(&dinner->forks[i].fork, NULL);
		dinner->forks[i].fork_index = i;
	}
	philos_init(dinner);
}
