/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoroutine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:11:02 by aamirkha          #+#    #+#             */
/*   Updated: 2024/06/26 17:02:23 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

inline void	__attribute__((always_inline)) __coma(t_philo *philo)
{
	t_value t = philo->table->time_to_eat * __SUPER__SECRET__PROPORTION__ - philo->table->time_to_sleep;

	if (t > 0)
	{
		ft_usleep(t / __SUPER__SECRET__PROPORTION__, philo->table);
	}
}

inline void	__attribute__((always_inline)) __think(t_philo *philo)
{
	philo_log(THINK, philo);

	if (philo->table->num_of_philos % 2 != 0)
	{
		__coma(philo);
	}
}

inline void	__attribute__((always_inline)) __sleep(t_philo *philo)
{
	philo_log(SLEEP, philo);
	ft_usleep(philo->table->time_to_sleep, philo->table);
}

static void __attribute__((hot))	__eat(t_philo *philo)
{
	int	first;
	int	second;

	first = (philo->id % 2 == 0);

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
	__unlock(&(philo->forks[first]->mtx));
	__unlock(&(philo->forks[second]->mtx));
}

static void	__desync(t_philo *philo)
{
	if (philo->table->num_of_philos % 2 == 0 && (philo->id % 2 == 0))
	{
		ft_usleep(__ANOTHER_SUPER__SECRET__PROPORTION__ * MILLISECOND, philo->table);
	}
	else if (philo->table->num_of_philos % 2 != 0 && (philo->id % 2 != 0))
	{
		__coma(philo);
	}
}

void	*philo_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;

	wait_for_other_philos(philo->table);

	set_val(&philo->mtx, &philo->time_last_meal, get_time(MILLISECOND));
	inc_val(&(philo->table->mtx), &(philo->table->active_threads));
	__desync(philo);
	while (!get_val(&philo->mtx, &philo->full) && !dinner_finished(philo->table))
	{
		__eat(philo);
		__sleep(philo);
		__think(philo);
	}
	return (data);
}
