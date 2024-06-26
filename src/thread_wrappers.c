/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_wrappers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 20:18:21 by aamirkha          #+#    #+#             */
/*   Updated: 2024/06/26 20:42:01 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	__thread_err(int status, t_opcode opcode)
{
	if (EAGAIN == status)
		__exit("No resources to create another thread", __scary_error_info__);
	else if (EPERM == status)
		__exit("The caller does not have appropriate permission\n", __scary_error_info__);
	else if (EINVAL == status && CREATE == opcode)
		__exit("The value specified by attr is invalid.", __scary_error_info__);
	else if (EINVAL == status && (JOIN == opcode || DETACH == opcode))
		__exit("The value specified by thread is not joinable\n", __scary_error_info__);
	else if (ESRCH == status)
		__exit("No thread could be found corresponding to that"
			"specified by the given thread ID, thread.", __scary_error_info__);
	else if (EDEADLK == status)
		__exit("A deadlock was detected or the value of"
			"thread specifies the calling thread.", __scary_error_info__);
}

static void	thread_wrapper(pthread_t *thread, t_fptr f, void *data, t_opcode opcode)
{
	if (CREATE == opcode)
		__thread_err(pthread_create(thread, NULL, f, data), opcode);
	else if (JOIN == opcode)
		__thread_err(pthread_join(*thread, NULL), opcode);
	else if (DETACH == opcode)
		__thread_err(pthread_detach(*thread), opcode);
}

void	__create(pthread_t *thread, t_fptr f, void *data)
{
	thread_wrapper(thread, f, data, CREATE);
}

void	__join(pthread_t *thread)
{
	thread_wrapper(thread, NULL, NULL, JOIN);
}

void	__attribute__((unused))	__detach(pthread_t *thread)
{
	thread_wrapper(thread, NULL, NULL, DETACH);
}
