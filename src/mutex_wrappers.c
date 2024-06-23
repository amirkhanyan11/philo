/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   human_readable_wrappers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 20:15:32 by aamirkha          #+#    #+#             */
/*   Updated: 2024/06/23 20:17:47 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_wrapper(t_mutex *mutex, t_opcode opcode)
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

void __attribute__((always_inline)) __lock(t_mutex *mutex)
{
	mutex_wrapper(mutex, LOCK);
}

void __attribute__((always_inline)) __unlock(t_mutex *mutex)
{
	mutex_wrapper(mutex, UNLOCK);
}

void __attribute__((always_inline)) __init(t_mutex *mutex)
{
	mutex_wrapper(mutex, INIT);
}

void __attribute__((always_inline)) __destroy(t_mutex *mutex)
{
	mutex_wrapper(mutex, DESTROY);
}