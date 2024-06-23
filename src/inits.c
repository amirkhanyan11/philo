/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 18:02:58 by aamirkha          #+#    #+#             */
/*   Updated: 2024/06/23 17:49:15 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_table *table_init(int ac, char **av)
{
	t_table *table = ft_malloc (sizeof(t_table));

	table->num_of_philos = matoi(av[__number_of_philosophers]);
	if (ac == 6)
		table->times_each_eat = matoi(av[__number_of_times_each_philosopher_must_eat]);
	else
		table->times_each_eat = -1;


	table->time_to_die = matoi(av[__time_to_die]) * MILLISECOND;
	table->time_to_eat = matoi(av[__time_to_eat]) * MILLISECOND;
	table->time_to_sleep = matoi(av[__time_to_sleep]) * MILLISECOND;

	table->start_sim = 0;
	table->end_sim = 0;
	table->all_set = 0;
	table->active_threads = 0;

	safe_mutex_op(&table->mtx, INIT);
	safe_mutex_op(&table->iomtx, INIT);
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

		safe_mutex_op(&(table->philos_arr[i].mtx), INIT);

		table->philos_arr[i].time_last_meal = INT_MAX;
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
		safe_mutex_op(&(table->forks_arr[i].mtx), INIT);
		table->forks_arr[i].id = i;
		i++;
	}
}

