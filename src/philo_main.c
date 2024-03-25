/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:47:48 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/03/25 17:30:53 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

//number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

pthread_mutex_t mutex;

void	*roll_dice()
{
	int	value;
	int *result;
	
	pthread_mutex_lock(&mutex);
	result = malloc(sizeof(int));
	value = (rand() % 6) + 1;
	*result = value;
	pthread_mutex_unlock(&mutex);
	return (void*) result;
}

int     main(int argc, char **argv)
{
	(void)argv;
	(void)argc;
/*     if (argc < 5 || argc > 6)
		args_error(); */

	srand(time(NULL));
	int *res;
	pthread_t	th[4];
	pthread_mutex_init(&mutex, NULL);
	for (int i = 0; i < 4; i++)
	{
		pth_check(pthread_create(&th[i], NULL, &roll_dice, NULL));
		printf("STARTED ROLLING %d\n", i);
	}
	for (int i = 0; i < 4; i++)
	{
		pth_check(pthread_join(th[i], (void **) &res));
		printf("DICE %d ROLLED: %d\n", i, *res);
		printf("FINISHED ROLLING %d\n", i);
		free(res);
	}
	pthread_mutex_destroy(&mutex);
	return 0;
}
