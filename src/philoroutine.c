/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoroutine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:11:02 by aamirkha          #+#    #+#             */
/*   Updated: 2024/06/13 13:05:37 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void eat(t_philo *philo)
{
	int first = left, second = right;

	if (philo->id % 2 == 0)
		first = right;
	second = !first;

	safe_mutex_op(&(philo->forks[first]->mtx), LOCK);
	philo_log(TAKE_FORK, philo);
	safe_mutex_op(&(philo->forks[second]->mtx), LOCK);
	philo_log(TAKE_FORK, philo);

	set_val(&(philo->mtx), &(philo->time_last_meal), get_time(MILLISECOND));
	philo->meal_count++;
	philo_log(EAT, philo);
	ft_usleep(philo->time_to_eat, philo->table);

	if (philo->table->times_each_eat > 0 && philo->meal_count == philo->table->times_each_eat)
		set_val(&(philo->mtx), &(philo->full), 1);

	safe_mutex_op(&(philo->forks[second]->mtx), UNLOCK);
	safe_mutex_op(&(philo->forks[first]->mtx), UNLOCK);

}

void think(t_philo *philo)
{
	philo_log(THINK, philo);
}

void philo_log(t_philo_op opcode, t_philo *philo)
{
	safe_mutex_op(&(philo->table->iomtx), LOCK);
	if (!dinner_finished(philo->table))
	{
		if (TAKE_FORK == opcode)
		{
			printf("%ld %d has taken a fork\n", get_time(MILLISECOND) - philo->table->start_sim, philo->id);
		}
		else if (EAT == opcode)
		{
			printf("%ld %d is eating\n", get_time(MILLISECOND) - philo->table->start_sim, philo->id);
		}
		else if (SLEEP == opcode)
		{
			printf("%ld %d is sleeping\n", get_time(MILLISECOND) - philo->table->start_sim, philo->id);
		}
		else if (THINK == opcode)
		{
			printf("%ld %d is thinking\n", get_time(MILLISECOND) - philo->table->start_sim, philo->id);
		}
	}
	safe_mutex_op(&(philo->table->iomtx), UNLOCK);
}



void *ph_routine(void *data)
{
	t_philo * philo = (t_philo *)data;
	wait4all(philo->table);

	while (!philo->full && !dinner_finished(philo->table))
	{
		eat(philo);

		philo_log(SLEEP, philo);
		ft_usleep(philo->time_to_sleep, philo->table);

		think(philo);
	}

	return data;
}
