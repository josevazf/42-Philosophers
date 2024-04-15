/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:56:38 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/04/08 12:05:54 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	setup_dinner(t_table *table)
{
	table->finished = false;
	table->philos = safe_malloc(table->nb_philos);
	
}

void	safe_mutex(t_mutex *mutex, )