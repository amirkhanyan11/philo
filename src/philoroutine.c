/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoroutine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:11:02 by aamirkha          #+#    #+#             */
/*   Updated: 2024/04/28 21:36:19 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *ph_routine(void *data)
{
	t_philo * philo = (t_philo *)data;
	int i = 0;
	while (i < 2)
	{
		pthread_mutex_lock(&(philo->forks[left]->mtx));
		pthread_mutex_lock(&(philo->forks[right]->mtx));

		sleep(4);
		printf ("philo %d is eating\n", philo->id);

		pthread_mutex_unlock(&(philo->forks[left]->mtx));
		pthread_mutex_unlock(&(philo->forks[right]->mtx));

		sleep(4);
		printf ("philo %d is sleeping\n", philo->id);
		i++;
	}
	return philo;
}


