/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:47:48 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/04/29 19:07:44 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

//number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

int     main(int argc, char **argv)
{
	t_dinner	dinner;
	
	if (argc < 5 || argc > 6)
		return (args_error());
	check_input(&dinner, argv);
	setup_dinner(&dinner);
	start_dinner(&dinner);
	cleanup(&dinner);
}
