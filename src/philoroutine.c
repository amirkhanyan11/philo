/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoroutine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:11:02 by aamirkha          #+#    #+#             */
/*   Updated: 2024/06/25 12:13:09 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// __attribute__((no_sanitize_thread))
void __eat(t_philo *philo)
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
	ft_usleep(philo->table->time_to_eat, philo->table);

	if (has_value(&philo->table->times_each_eat) && philo->meal_count == value(&philo->table->times_each_eat))
		set_val(&(philo->mtx), &(philo->full), true);

	__unlock(&(philo->forks[second]->mtx));
	__unlock(&(philo->forks[first]->mtx));
}

static void  __think(t_philo *philo)
{
	philo_log(THINK, philo);
	// ft_usleep(100000, philo->table);
}

void philo_log(t_opcode opcode, t_philo *philo)
{
	__lock(&(philo->table->iomtx));
	if (!dinner_finished(philo->table))
	{
		if (TAKE_FORK == opcode)
		{
			printf("%ld %ld has taken a fork\n", get_time(MILLISECOND) - philo->table->start_sim, philo->id);
		}
		else if (EAT == opcode)
		{
			printf(CYAN);
			printf("%ld %ld is eating\n", get_time(MILLISECOND) - philo->table->start_sim, philo->id);
			printf(RESET);
		}
		else if (SLEEP == opcode)
		{
			// printf(CYAN);
			printf("%ld %ld is sleeping\n", get_time(MILLISECOND) - philo->table->start_sim, philo->id);
			// printf(RESET);
		}
		else if (THINK == opcode)
		{
			printf("%ld %ld is thinking\n", get_time(MILLISECOND) - philo->table->start_sim, philo->id);
		}
		else if (DIE == opcode)
		{
			printf(RED);
			printf("%ld %ld died\n", get_time(MILLISECOND) - philo->table->start_sim, philo->id);
			printf(RESET);
		}
	}
	__unlock(&(philo->table->iomtx));
}

static void  __sleep(t_philo *philo)
{
	philo_log(SLEEP, philo);
	ft_usleep(philo->table->time_to_sleep, philo->table);
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

void *philo_routine(void *data)
{
	t_philo * philo = (t_philo *)data;
	wait_for_other_philos(philo->table);

	set_val(&philo->table->mtx, &philo->time_last_meal, get_time(MILLISECOND));

	inc_val(&(philo->table->mtx), &(philo->table->active_threads));

	__desync(philo);

	while (!get_val(&philo->mtx, &philo->full) && !dinner_finished(philo->table))
	{
		__eat(philo);

		__sleep(philo);

		__think(philo);
	}

	return data;
}

bool is_dead(t_philo *philo)
{
	if (get_val(&philo->mtx, &(philo->full)) == true) return false;

	t_value elapsed = get_time(MILLISECOND) - get_val(&philo->mtx, &(philo->time_last_meal));

	return elapsed > (get_val(&(philo->table->mtx), &(philo->table->time_to_die)) / MILLISECOND);
}

void *observer_routine(void * data)
{
	t_table * table = (t_table *)data;

	while (0 == check_equality(&table->mtx, &table->active_threads, table->num_of_philos));

	while (!dinner_finished(table))
	{
		int i = 0;
		while (i < table->num_of_philos && !dinner_finished(table))
		{
			if (is_dead(table->philos_arr + i))
			{
				philo_log(DIE, &table->philos_arr[i]);
				set_val(&table->mtx, &table->end_sim, true);
				set_val(&table->mtx, &table->philos_arr[i].dead, true);
			}
			i++;
		}
	}
	return data;
}
