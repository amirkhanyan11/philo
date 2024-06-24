/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 18:02:58 by aamirkha          #+#    #+#             */
/*   Updated: 2024/06/23 21:06:13 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_table *table_init(int ac, char **av)
{
	t_optional num_of_philos = matoi(av[__number_of_philosophers]);
	t_optional time_to_die = matoi(av[__time_to_die]);
	t_optional time_to_eat = matoi(av[__time_to_eat]);
	t_optional time_to_sleep = matoi(av[__time_to_sleep]);

	if (any_of(4, doesnt_have_value, num_of_philos, time_to_die, time_to_sleep, time_to_eat) || any_of(3, has_bad_timeval, time_to_die, time_to_sleep, time_to_eat) || value(&num_of_philos) < 1 || value(&num_of_philos) > PHILO_MAX)
	{
		__exit("Bad argument values");
	}

	t_table *table = ft_malloc (sizeof(t_table));

	table->num_of_philos = value(&num_of_philos);
	if (ac == 6)
	{
		t_optional times_each_eat = matoi(av[__number_of_times_each_philosopher_must_eat]);
		set_optional(&table->times_each_eat, value(&times_each_eat));
	}
	else
		table->times_each_eat = make_optional();


	table->time_to_die = value(&time_to_die) * MILLISECOND;
	table->time_to_eat = value(&time_to_eat) * MILLISECOND;
	table->time_to_sleep = value(&time_to_sleep) * MILLISECOND;
	

	table->end_sim = false;
	table->all_set = false;
	table->start_sim = 0;
	table->active_threads = 0;

	__init(&table->mtx);
	__init(&table->iomtx);
	forks_init(table);
	philos_init(table);

	return table;
}


void philos_init(t_table * table)
{
	table->philos_arr = ft_malloc(sizeof(t_philo) * table->num_of_philos);

	int i = 0;
	while (i < table->num_of_philos)
	{
		table->philos_arr[i].id = i;
		table->philos_arr[i].forks[left] = &(table->forks_arr[i]);
		table->philos_arr[i].forks[right] = &(table->forks_arr[(table->num_of_philos + i - 1) % table->num_of_philos]); // uuuu jenerig

		__init(&(table->philos_arr[i].mtx));

		table->philos_arr[i].time_last_meal = 0;
		table->philos_arr[i].dead = 0;
		table->philos_arr[i].full = 0;
		table->philos_arr[i].meal_count = 0;
		table->philos_arr[i].table = table;
		i++;
	}
}

void forks_init(t_table * table)
{
	table->forks_arr = ft_malloc (sizeof(t_fork) * table->num_of_philos);
	int i = 0;
	while (i < table->num_of_philos)
	{
		__init(&(table->forks_arr[i].mtx));
		table->forks_arr[i].id = i;
		i++;
	}
}

