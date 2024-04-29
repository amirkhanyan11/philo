/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoroutine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:11:02 by aamirkha          #+#    #+#             */
/*   Updated: 2024/04/29 16:15:13 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ph_eat(t_philo *philo, timeval_t *time)
{

	printf ("timestamp %ld : philo %d is eating\n", time->tv_sec, philo->id);
	philo->time_last_meal = time->tv_sec;
	sleep(philo->time_to_eat);
}

void ph_sleep(t_philo *philo, timeval_t *time)
{
	printf ("timestamp %ld : philo %d is sleeping\n", time->tv_sec, philo->id);
	sleep(philo->time_to_sleep);
}

int can_eat(t_philo *philo)
{
	printf("philo %d asks for waiter!\n", philo->id);
	pthread_create(&(philo->waiter->tid), NULL, w_routine, philo->table);
	pthread_join(philo->waiter->tid, NULL);

	return (philo->can_i_eat);
}

int pick_forks(t_philo *philo, timeval_t *time)
{
	int first = left, second = right;

	// if (philo->id % 2 == 0)
	// 	first = right;
	// second = !first;

	if (philo->forks[first]->being_used == 0 && philo->forks[second]->being_used == 0)
	{
		philo->forks[first]->being_used = 1;
		pthread_mutex_lock(&(philo->forks[first]->mtx));
		printf ("timestamp %ld : philo %d picked up fork %d \n", time->tv_sec, philo->id, philo->forks[first]->id);
		philo->forks[second]->being_used = 1;
		pthread_mutex_lock(&(philo->forks[second]->mtx));
		printf ("timestamp %ld : philo %d picked up fork %d \n", time->tv_sec, philo->id, philo->forks[second]->id);
		return 1;
	}
	return 0;
}


void drop_forks(t_philo *philo, timeval_t *time)
{
	int first = left, second = right;

	// if (philo->id % 2 == 0)
	// 	first = right;
	// second = !first;


	philo->forks[first]->being_used = 0;
	pthread_mutex_unlock(&(philo->forks[first]->mtx));
	printf ("timestamp %ld : philo %d putted down fork %d \n", time->tv_sec, philo->id, philo->forks[first]->id);
	philo->forks[second]->being_used = 0;
	pthread_mutex_unlock(&(philo->forks[second]->mtx));
	printf ("timestamp %ld : philo %d putted down fork %d \n", time->tv_sec, philo->id, philo->forks[second]->id);

}


void *ph_routine(void *data)
{
	t_philo * philo = (t_philo *)data;
	int i = 0;


	timeval_t time;

	while (i < philo->table->times_each_eat)
	{
		gettimeofday(&time, NULL);

		if (can_eat(philo))
		{
			int picked = pick_forks(philo, &time);


			if (picked)
			{
				ph_eat(philo, &time);
				drop_forks(philo, &time);
			}
			i++;
		}

		ph_sleep(philo, &time);
	}
	philo->dead = 1;
	return data;
}
