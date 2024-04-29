/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:41:39 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/04/29 19:08:08 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* Write philo action using a thread safe method */
void	print_action(t_philo_act action, t_philo *philo)
{
	long	elapsed_t;

	elapsed_t = get_current_time() - philo->dinner->start_time;
	if (philo->hungry == false)
		return ;
	safe_mutex(&philo->dinner->print_mutex, LOCK);
	if ((action == TAKE_FIRST_FORK || action == TAKE_SECOND_FORK) \
		&& !sim_finished(philo->dinner))
		printf("%ld %d has taken a fork\n", elapsed_t, philo->index);
	else if (action == EATING && !sim_finished(philo->dinner))
		printf("%ld %d is eating\n", elapsed_t, philo->index);
	else if (action == SLEEPING && !sim_finished(philo->dinner))
		printf("%ld %d is sleeping\n", elapsed_t, philo->index);
	else if (action == THINKING && !sim_finished(philo->dinner))
		printf("%ld %d is thinking\n", elapsed_t, philo->index);
	else if (action == DIED)
		printf("%ld %d died\n", elapsed_t, philo->index);
	safe_mutex(&philo->dinner->print_mutex, UNLOCK);
}

/* Usleep function adjusted for precision */
void	usleep_redux(long sleep_t, t_dinner *dinner)
{
	struct timeval	start_t;
	struct timeval	elapsed_t;
	long			remain_t;
	
	gettimeofday(&start_t, NULL);
	while (1)
	{
		if (sim_finished(dinner))
			break ;
		gettimeofday(&elapsed_t, NULL);
		remain_t = (elapsed_t.tv_sec - start_t.tv_sec) * 1000
			+ (elapsed_t.tv_usec - start_t.tv_usec) / 1000;
		if (remain_t >= sleep_t)
			break ;
		usleep(100);
	}
	return ;
}

/* Usleep function adjusted for precision */
/* void	usleep_redux(long sleep_t, t_dinner *dinner)
{
	long	start_t;
	long	elapsed_t;
	long	remain_t;
	
	start_t = get_current_time();
	while (sleep_t > get_current_time() - start_t)
	{
		if (sim_finished(dinner))
			break ;
		elapsed_t = get_current_time() - start_t;
		remain_t = sleep_t - elapsed_t;
		if (remain_t > 1e6)
			usleep(remain_t / 2);
		else
		{
			while (sleep_t > get_current_time() - start_t)
				;
		}
	}
} */
	
/* Get current time in the desired format: s, ms or us */
long	get_current_time()
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
}

void	cleanup(t_dinner *dinner)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < dinner->nb_philos)
	{
		philo = &dinner->philos[i];
		safe_mutex(&philo->philo_mutex, DESTROY);
	}
	safe_mutex(&dinner->print_mutex, DESTROY);
	safe_mutex(&dinner->dinner_mutex, DESTROY);
	free(dinner->forks);
	free(dinner->philos);
}
