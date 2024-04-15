/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:03:22 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/04/15 15:33:32 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void handle_safe_mutex(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (opcode == LOCK || opcode == UNLOCK \
		|| opcode == DESTROY))
		exit_error("The value specified by mutex is invalid\n");
	else if (status == EINVAL && opcode == INIT)
		exit_error("The value specified by attr is invalid\n.");
	else if (status == EDEADLK)
		exit_error("A deadlock could occur if the thread blocked waiting for mutex\n");
	else if (status == EPERM)
		exit_error("The current thread does not hold a lock on mutex\n");
	else if (status == ENOMEM)
		exit_error("The process cannot allocate enough memory to create another mutex\n");
	else if (status == EBUSY)
		exit_error("Mutex is locked\n");
}

void	safe_mutex(t_mutex *mutex, t_opcode opcode)
{
	if (opcode == INIT)
		handle_safe_mutex(pthread_mutex_init(mutex, NULL), opcode);
	else if (opcode == LOCK)
		handle_safe_mutex(pthread_mutex_lock(mutex), opcode);
	else if (opcode == UNLOCK)
		handle_safe_mutex(pthread_mutex_unlock(mutex), opcode);
	else if (opcode == DESTROY)
		handle_safe_mutex(pthread_mutex_destroy(mutex), opcode);
	else
		exit_error("Wrong opcode input");
}

void	handle_safe_thread(int status, t_opcode opcode)
{
	if (statu == 0)
		return ;
	else if (status == EAGAIN)
		exit_error("No resources to create another thread\n");
	else if (status == EPERM)
		exit_error("The caller does not have appropriate permission\n");
	else if (status == EINVAL && opcode == CREATE)
		exit_error("The value specified by attr is invalid\n");
	else if (status == EINVAL && (opcode == JOIN || opcode == DETACH))
		exit_error("The value specified by thread is not joinable\n");
	else if (status == ESRCH)
		exit_error("No thread could be found corresponding to that"
			"specified by the given thread ID, thread\n");
	else if (status == EDEADLK)
		exit_error("A deadlock was detected or the value of thread"
			"specifies the calling thread\n");
}

void	safe_thread(pthread_t *thread, void *(*func)(void *), void *data, t_opcode opcode)
{
	if (opcode == CREATE)
		handle_safe_thread(pthread_create(thread, NULL, func, data), opcode);
	else if (opcode == JOIN)
		handle_safe_thread(pthread_join(*thread, NULL), opcode);
	else if (opcode == DETACH)
		handle_safe_thread(pthread_detach(*thread), opcode);
	else
		exit_error("Wrong opcode input\n");
}
