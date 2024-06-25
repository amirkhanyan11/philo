/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoroutine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:11:02 by aamirkha          #+#    #+#             */
/*   Updated: 2024/06/25 13:15:48 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

inline void __attribute__((always_inline))	__think(t_philo *philo)
{
	philo_log(THINK, philo);
}

inline void __attribute__((always_inline))	__sleep(t_philo *philo)
{
	philo_log(SLEEP, philo);
	ft_usleep(philo->table->time_to_sleep, philo->table);
}

void	__eat(t_philo *philo)
{
	int	first;
	int	second;

	first = left;
	if (philo->id % 2 == 0)
		first = right;
	second = !first;
	__lock(&(philo->forks[first]->mtx));
	philo_log(TAKE_FORK, philo);
	__lock(&(philo->forks[second]->mtx));
	philo_log(TAKE_FORK, philo);
	set_val(&(philo->mtx), &(philo->time_last_meal), get_time(MILLISECOND));
	philo->meal_count++;
	philo_log(EAT, philo);
	ft_usleep(philo->table->time_to_eat, philo->table);
	if (has_value(&philo->table->times_each_eat)
		&& philo->meal_count == value(&philo->table->times_each_eat))
		set_val(&(philo->mtx), &(philo->full), true);
	__unlock(&(philo->forks[second]->mtx));
	__unlock(&(philo->forks[first]->mtx));
}

static void	__desync(t_philo *philo)
{
	if (philo->table->num_of_philos % 2 == 0 && (philo->id % 2 == 0))
	{
		ft_usleep(30 * MILLISECOND, philo->table);
	}
	else if (philo->table->num_of_philos % 2 != 0 && (philo->id % 2 != 0))
	{
		__think(philo);
	}
}

void	*philo_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_for_other_philos(philo->table);
	set_val(&philo->table->mtx, &philo->time_last_meal, get_time(MILLISECOND));
	inc_val(&(philo->table->mtx), &(philo->table->active_threads));
	__desync(philo);
	while (!get_val(&philo->mtx, &philo->full)
		&& !dinner_finished(philo->table))
	{
		__eat(philo);
		__sleep(philo);
		__think(philo);
	}
	return (data);
}
