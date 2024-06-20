/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:20:23 by aamirkha          #+#    #+#             */
/*   Updated: 2024/06/20 14:56:53 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_malloc(size_t n)
{
	void	*ptr;

	ptr = malloc(n);
	if (NULL == ptr)
		__exit("Bad alloc");
	return (ptr);
}

static void	__mutex_err(int status)
{
	if (0 == status)
		return ;
	if (EINVAL == status)
		__exit("The value specified by mutex is invalid");
	else if (EDEADLK == status)
		__exit("A deadlock would occur if the thread "
			"blocked waiting for mutex.");
	else if (EPERM == status)
		__exit("The current thread does not hold a lock on mutex.");
	else if (ENOMEM == status)
		__exit("The process cannot allocate enough memory"
			" to create another mutex.");
	else if (EBUSY == status)
		__exit("Mutex is busy");
}

static void	__thread_err(int status, t_opcode opcode) // ??
{
	if (0 == status)
		return ;
	if (EAGAIN == status)
		__exit("No resources to create another thread");
	else if (EPERM == status)
		__exit("The caller does not have appropriate permission\n");
	else if (EINVAL == status && CREATE == opcode)
		__exit("The value specified by attr is invalid.");
	else if (EINVAL == status && (JOIN == opcode || DETACH == opcode))
		__exit("The value specified by thread is not joinable\n");
	else if (ESRCH == status)
		__exit("No thread could be found corresponding to that"
			"specified by the given thread ID, thread.");
	else if (EDEADLK == status)
		__exit("A deadlock was detected or the value of thread specifies the calling thread.");
}

void __lock(pthread_mutex_t *mutex)
{
	safe_mutex_op(mutex, LOCK);
}

void __unlock(pthread_mutex_t *mutex)
{
	safe_mutex_op(mutex, UNLOCK);
}

void	safe_mutex_op(pthread_mutex_t *mutex, t_opcode opcode)
{
	if (LOCK == opcode)
		__mutex_err(pthread_mutex_lock(mutex));
	else if (UNLOCK == opcode)
		__mutex_err(pthread_mutex_unlock(mutex));
	else if (INIT == opcode)
		__mutex_err(pthread_mutex_init(mutex, NULL));
	else if (DESTROY == opcode)
		__mutex_err(pthread_mutex_destroy(mutex));
}

long	get_val(pthread_mutex_t *mutex, long *value)
{
	long	ret;

	__lock(mutex);
	ret = *value;
	__unlock(mutex);
	return (ret);
}

void	set_val(pthread_mutex_t *mutex, long *dest, long value)
{
	__lock(mutex);
	*dest = value;
	__unlock(mutex);
}

void	inc_val(pthread_mutex_t *mutex, long *val)
{
	__lock(mutex);
	++(*val);
	__unlock(mutex);
}

int	check_equality(pthread_mutex_t *mutex, long *lhv, long rhv)
{
	int res;
	
	__lock(mutex);
	res = (*lhv == rhv);
	__unlock(mutex);

	return res;
}

int dinner_finished(t_table * table)
{
	return get_val(&(table->mtx), &(table->end_sim));
}

void	safe_thread_op(pthread_t *thread, t_fptr f, void *data, t_opcode opcode)
{
	if (CREATE == opcode)
		__thread_err(pthread_create(thread, NULL, f, data), opcode);
	else if (JOIN == opcode)
		__thread_err(pthread_join(*thread, NULL), opcode);
	else if (DETACH == opcode)
		__thread_err(pthread_detach(*thread), opcode);
}


