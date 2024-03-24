/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:41:39 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/03/24 18:35:08 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* Converts the string argument 'nstr' to an integer.
   This function returns the converted integral number as an int value. 
   If no valid conversion could be performed, it returns zero. */
int	ft_atoi(const char *nstr)
{
	size_t	i;
	int		sign;
	int		nb;

	nb = 0;
	sign = 1;
	i = 0;
	while ((nstr[i] >= 9 && nstr[i] <= 13) || nstr[i] == 32)
		i++;
	if (nstr[i] == '-' || nstr[i] == '+')
	{
		if (nstr[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (nstr[i] >= '0' && nstr[i] <= '9')
		nb = nb * 10 + nstr[i++] - '0';
	return (nb * sign);
}
