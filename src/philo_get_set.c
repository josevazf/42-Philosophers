/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_get_set.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:49:17 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/04/16 09:53:37 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


/* Allows a safe access to change a bool variable using a mutex */
void	set_bool(t_mutex *mutex, bool *dest, bool value)
{
	handle_safe_mutex(mutex, LOCK);
	*dest = value;
	handle_safe_mutex(mutex, UNLOCK);
}

/* Allows a safe access to read a bool variable using a mutex */
bool	get_bool(t_mutex *mutex, bool *value)
{
	bool	res;
	
	handle_safe_mutex(mutex, LOCK);
	res = *value;
	handle_safe_mutex(mutex, UNLOCK);
	return (res);
}

/* Allows a safe access to read a long variable using a mutex */
void	set_long(t_mutex *mutex, long *dest, long value)
{
	handle_safe_mutex(mutex, LOCK);
	*dest = value;
	handle_safe_mutex(mutex, UNLOCK);
}

/* Allows a safe access to read a long variable using a mutex */
long	get_long(t_mutex *mutex, long *value)
{
	long	res;
	
	handle_safe_mutex(mutex, LOCK);
	res = *value;
	handle_safe_mutex(mutex, UNLOCK);
	return (res);
}
