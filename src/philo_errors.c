/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:32:37 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/04/16 12:58:09 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*safe_malloc(size_t bytes)
{
	void *output;

	output = malloc(bytes);
	if (output == NULL)
		exit_error("philo: malloc error\n");
	return (output);
}

/* Deal with bad arguments */
int		args_error(void)
{
	printf("philo usage: ./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
	printf("\tex.: ./philo 3 600 150 150 [5]\n");
	exit(EXIT_FAILURE);
}

void	exit_error(const char *str)
{
	printf("%s\n", str);
	exit (EXIT_FAILURE);
}
