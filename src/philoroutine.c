/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoroutine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:11:02 by aamirkha          #+#    #+#             */
/*   Updated: 2024/06/23 17:11:47 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void eat(t_philo *philo)
{
	int first = left, second = right;

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
	ft_usleep(philo->time_to_eat, philo->table);

	if (philo->table->times_each_eat > 0 && philo->meal_count == philo->table->times_each_eat)
		set_val(&(philo->mtx), &(philo->full), 1);

	__unlock(&(philo->forks[second]->mtx));
	__unlock(&(philo->forks[first]->mtx));

}

void think(t_philo *philo)
{
	philo_log(THINK, philo);
	// ft_usleep(100000, philo->table);
}

void philo_log(t_philo_op opcode, t_philo *philo)
{
	__lock(&(philo->table->iomtx));
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
		else if (DIE == opcode)
		{
			printf("%ld %d died\n", get_time(MILLISECOND) - philo->table->start_sim, philo->id);
		}
	}
	__unlock(&(philo->table->iomtx));
}

void *ph_routine(void *data)
{
	t_philo * philo = (t_philo *)data;
	wait4all(philo->table);

	set_val(&philo->table->mtx, &philo->time_last_meal, get_time(MILLISECOND));

	inc_val(&(philo->table->mtx), &(philo->table->active_threads));

	while (!philo->full && !dinner_finished(philo->table))
	{
		eat(philo);

		ft_usleep(philo->time_to_sleep, philo->table);
		philo_log(SLEEP, philo);

		think(philo);
	}

	return data;
}


void *ob_routine(void * data)
{
	t_table * table = (t_table *)data;

	while (0 == check_equality(&table->mtx, &table->active_threads, table->num_of_philos));

	// printf("ready : %ld\n", get_val(&table->mtx, &table->active_threads));

	while (!dinner_finished(table))
	{
		int i = 0;
		while (i < table->num_of_philos && !dinner_finished(table))
		{
			if (0 == get_val(&table->mtx, &(table->philos_arr[i].full)) && get_time(MILLISECOND) - get_val(&table->mtx, &(table->philos_arr[i].time_last_meal)) > (table->philos_arr[i].time_to_die / MILLISECOND))
			{
				philo_log(DIE, &table->philos_arr[i]);
				set_val(&table->mtx, &table->end_sim, 1);
				set_val(&table->mtx, &table->philos_arr[i].dead, 1);
			}
			// printf("Dinner finished : %ld : %ld\n", get_time(MILLISECOND) - get_val(&table->mtx, &(table->philos_arr[i].time_last_meal)), table->philos_arr[i].time_to_die);
			i++;
		}
	}
	return data;
}
