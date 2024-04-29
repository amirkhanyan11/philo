/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 18:02:58 by aamirkha          #+#    #+#             */
/*   Updated: 2024/04/29 15:55:32 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static int _is_correct_table(t_table *table)
// {
// 	// > 0 esh
// 	return (table->num_of_philos && table->time_to_die && table->time_to_eat && table->time_to_sleep && table->times_each_eat);
// }

t_table *table_init(int ac, char **av)
{
	t_table *table = malloc (sizeof(t_table));

	table->num_of_philos = matoi(av[__number_of_philosophers]);
	if (ac == 6)
		table->times_each_eat = matoi(av[__number_of_times_each_philosopher_must_eat]);
	else
		table->times_each_eat = -1;


	forks_init(table);
	waiter_init(table);
	philos_init(table, av);

	// if (!_is_correct_table(table))
	// {
	// 	table_destroy(table);
	// 	__exit("Bad args :(\n");
	// }

	return table;
}

void waiter_init(t_table *table)
{
	table->waiter = malloc(sizeof(t_waiter));
}


void philos_init(t_table * table, char **av)
{
	table->philos_arr = malloc(sizeof(t_philo) * table->num_of_philos);

	int i = 0;
	while (i < table->num_of_philos)
	{
		table->philos_arr[i].id = i;
		table->philos_arr[i].forks[left] = &(table->forks_arr[i]);
		table->philos_arr[i].forks[right] = &(table->forks_arr[(table->num_of_philos + i - 1) % table->num_of_philos]); // uuuu jenerig

		table->philos_arr[i].time_to_die = matoi(av[__time_to_die]);
		table->philos_arr[i].time_to_eat = matoi(av[__time_to_eat]);
		table->philos_arr[i].time_to_sleep = matoi(av[__time_to_sleep]);
		table->philos_arr[i].time_last_meal = LONG_MAX;
		table->philos_arr[i].dead = 0;
		table->philos_arr[i].can_i_eat = 0;
		table->philos_arr[i].waiter = table->waiter;
		table->philos_arr[i].table = table;
		i++;
	}
}

void forks_init(t_table * table)
{
	table->forks_arr = malloc (sizeof(t_fork) * table->num_of_philos);
	int i = 0;
	while (i < table->num_of_philos)
	{
		pthread_mutex_init(&(table->forks_arr[i].mtx), NULL);
		table->forks_arr[i].id = i;
		table->forks_arr[i].being_used = 0;
		i++;
	}
}

