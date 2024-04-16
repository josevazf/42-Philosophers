/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:32:39 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/04/16 13:09:15 by jrocha-v         ###   ########.fr       */
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
	if (nb > INT_MAX || nb <= 0)
		return (-1);
	return (nb);
}

void	check_input(t_dinner *dinner, char **argv)
{
	dinner->nb_philos = ft_atol_redux(argv[1]);
	if (dinner->nb_philos == -1)
		exit_error("Invalid 'number_of_philosophers'");
	dinner->tt_die = ft_atol_redux(argv[2]);
	if (dinner->tt_die == -1)
		exit_error("Invalid 'time_to_die'");
	dinner->tt_eat = ft_atol_redux(argv[3]);
	if (dinner->tt_eat == -1)
		exit_error("Invalid 'time_to_eat'");
	dinner->tt_sleep = ft_atol_redux(argv[4]);
	if (dinner->tt_sleep == -1)
		exit_error("Invalid 'time_to_sleep'");
	if (argv[5])
		dinner->nb_meals = ft_atol_redux(argv[5]);
	else
		dinner->nb_meals = -1;
}
