/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:21:06 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/04/15 17:44:29 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*dinner_sim(void *data)
{
	t_philo	*philo;
	
	philo = (t_philo *)data;
	await_philos(&dinner);

	
	return (NULL); 
}

void	start_dinner(t_dinner *dinner)
{
	int	i;
	
	i = -1;
	if (dinner->nb_meals == 0)
		return ;
	else if (dinner->nb_philos == 1)
		process_one_philo(&dinner); // to do
	else
	{
		while (++i < dinner->nb_philos)
		{
			handle_safe_thread(&dinner->philos[i].thread_index, dinner_sim, \
				&dinner->philos[i], CREATE);
		}
		 
	}
	
		
}