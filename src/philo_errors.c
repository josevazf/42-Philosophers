/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:03:22 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/03/25 15:03:13 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* Deal with bad arguments */
int	args_error(void)
{
	printf("philo usage: ./philo number_of_philosophers time_to_die time_to_eat ");
	printf("time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
	exit(EXIT_FAILURE);
}

int	pth_check(int pthread_ret)
{
	if (pthread_ret != 0)
		return (ERROR);
	else
		return (pthread_ret);
}
