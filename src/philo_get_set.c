/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_get_set.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:49:17 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/04/30 12:39:59 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* Allows a safe access to change a bool variable using a mutex */
void	set_bool(t_mutex *mutex, bool *dest, bool value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

/* Allows a safe access to read a bool variable using a mutex */
bool	get_bool(t_mutex *mutex, bool *value)
{
	bool	res;

	pthread_mutex_lock(mutex);
	res = *value;
	pthread_mutex_unlock(mutex);
	return (res);
}

/* Allows a safe access to read a long variable using a mutex */
void	set_long(t_mutex *mutex, long *dest, long value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

/* Allows a safe access to read a long variable using a mutex */
long	get_long(t_mutex *mutex, long *value)
{
	long	res;

	pthread_mutex_lock(mutex);
	res = *value;
	pthread_mutex_unlock(mutex);
	return (res);
}

/* Allows a safe access to increase a `long` variable using a mutex */
long	increase_long(t_mutex *mutex, long *value)
{
	pthread_mutex_lock(mutex);
	(*value)++;
	pthread_mutex_unlock(mutex);
	return (*value);
}
