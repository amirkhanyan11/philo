/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoroutine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:11:02 by aamirkha          #+#    #+#             */
/*   Updated: 2024/05/30 20:46:27 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void eat(t_philo *philo, timeval_t *time)
{
	int first = left, second = right;

	if (philo->id % 2 == 0)
		first = right;
	second = !first;

	safe_mutex_op(&(philo->forks[first]), LOCK);
	philo_log(TAKE_FORK, philo);
	safe_mutex_op(&(philo->forks[second]), LOCK);
	philo_log(TAKE_FORK, philo);

	set_val(&(philo->mtx), philo->time_last_meal, get_time(MILLISECOND));
	philo_log(EAT, philo);
	ft_usleep(philo->table->time_to_eat, philo->table);

	if (philo->table->times_each_eat == ++(philo->meal_count))
		set_bool(&(philo->mtx), &(philo->full), 1);

	safe_mutex_op(&(philo->forks[second]), UNLOCK);
	safe_mutex_op(&(philo->forks[first]), UNLOCK);

}

void think(t_philo *philo, timeval_t *time)
{
	
}

void philo_log(t_philo_op opcode, t_philo *philo)
{
	safe_mutex_op(&(philo->table->iomtx), LOCK);
	if (!dinner_finished(philo->table))
	{
		if (TAKE_FORK == opcode)
		{
			printf("%d %d has taken a fork\n", get_time(MILLISECOND) - philo->table->start_sim, philo->id);
		}
		else if (EAT == opcode)
		{
			printf("%d %d is eating\n", get_time(MILLISECOND) - philo->table->start_sim, philo->id);
		}
		else if (SLEEP == opcode)
		{
			printf("%d %d is sleeping\n", get_time(MILLISECOND) - philo->table->start_sim, philo->id);
		}
		else if (THINK == opcode)
		{
			printf("%d %d is thinking\n", get_time(MILLISECOND) - philo->table->start_sim, philo->id);
		}
	}
	safe_mutex_op(&(philo->table->iomtx), UNLOCK);
}



void *ph_routine(void *data)
{
	t_philo * philo = (t_philo *)data;
	wait4all(&philo->table);

	while (!philo->full && !dinner_finished(philo->table))
	{

	}
}
