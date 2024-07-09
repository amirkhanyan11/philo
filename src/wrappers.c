/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:20:23 by aamirkha          #+#    #+#             */
/*   Updated: 2024/06/29 17:37:02 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	__attribute__((malloc))	*ft_malloc(size_t n)
{
	void	*ptr;

	ptr = malloc(n);
	if (NULL == ptr)
		__exit("Bad alloc");
	return (ptr);
}

void	__mutex_err(int status)
{
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

t_value	get_val(t_mutex *mutex, t_value *value)
{
	t_value	ret;

	__lock(mutex);
	ret = *value;
	__unlock(mutex);
	return (ret);
}

void	set_val(t_mutex *mutex, t_value *dest, t_value value)
{
	__lock(mutex);
	*dest = value;
	__unlock(mutex);
}

void	inc_val(t_mutex *mutex, t_value *val)
{
	__lock(mutex);
	++(*val);
	__unlock(mutex);
}
