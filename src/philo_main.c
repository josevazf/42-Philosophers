/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:47:48 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/03/26 17:54:13 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

//number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]


int     main(int argc, char **argv)
{
	t_table		table;
	
	(void)argv;
	if (argc < 5 || argc > 6)
		args_error();
	check_input(&table, argv);
	//prepare_dinner(&table);
	//start_dinner(&table);
	//cleanup(&table);
}
