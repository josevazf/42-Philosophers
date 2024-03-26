/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:32:39 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/03/26 18:14:22 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* Checks whether a character `c` is numeric or not. */
int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

/* Converts the string argument `nstr` to a long.
   It will only accept one `+` sign and a number up to `INT_MAX`. 
   If no valid conversion could be performed, it returns `-1`. */
long	ft_atol_redux(const char *nstr)
{
	size_t	i;
	long	nb;

	nb = 0;
	i = 0;
	while ((nstr[i] >= 9 && nstr[i] <= 13) || nstr[i] == 32)
		i++;
	if (nstr[i] == '-' || nstr[i] == '+')
	{
		if (nstr[i] == '-')
			return (-1);
		i++;
	}
	if (nstr[i] == '+')
		return (-1);
	if (!ft_isdigit(nstr[i]))
		return (-1);
	while (nstr[i] >= '0' && nstr[i] <= '9')
		nb = nb * 10 + nstr[i++] - '0';
	if (nstr[i] != '\0' && !ft_isdigit(nstr[i++]))
		return (-1);
	if (nb > INT_MAX)
		return (-1);
	return (nb);
}

void	check_input(t_table *table, char **argv)
{
	table->nb_philos = ft_atol_redux(argv[1]);
	printf("%ld\n", table->nb_philos);
	if (table->nb_philos == -1)
		exit_error("Invalid 'number_of_philosophers'");
	table->tt_die = ft_atol_redux(argv[2]);
	printf("%ld\n", table->tt_die);
	if (table->tt_die == -1)
		exit_error("Invalid 'time_to_die'");
	table->tt_eat = ft_atol_redux(argv[3]);
	printf("%ld\n", table->tt_eat);
	if (table->tt_eat == -1)
		exit_error("Invalid 'time_to_eat'");
	table->tt_sleep = ft_atol_redux(argv[4]);
	printf("%ld\n", table->tt_sleep);
	if (table->tt_sleep == -1)
		exit_error("Invalid 'time_to_sleep'");
	if (argv[5])
		table->nb_meals = ft_atol_redux(argv[5]);
	else
		table->nb_meals = -1;
}