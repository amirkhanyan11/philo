/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:34:37 by aamirkha          #+#    #+#             */
/*   Updated: 2024/06/23 18:10:21 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *foo(void *data)
{
	t_philo *philo = (t_philo*)data;

	wait4all(philo->table);
	set_val(&philo->table->mtx, &philo->time_last_meal, get_time(MILLISECOND));
	inc_val(&(philo->table->mtx), &(philo->table->active_threads));
	philo_log(TAKE_FORK, philo);
	while(!dinner_finished(philo->table));
	return NULL;
}

void __begin(t_table * table)
{
	int i = 0;

	if (0 == table->times_each_eat) return ;

	if (table->num_of_philos == 1)
	{
		safe_thread_op(&(table->philos_arr[0].tid), foo, &(table->philos_arr[0]), CREATE);
	}

	else
	{
		while (i < table->num_of_philos)
		{
			// create threads
			safe_thread_op(&(table->philos_arr[i].tid), philo_routine, &(table->philos_arr[i]), CREATE);
			i++;
		}
	}
	safe_thread_op(&(table->observer), observer_routine, table, CREATE);

	// notify that all threads are ready
	table->start_sim = get_time(MILLISECOND);
	set_val(&table->mtx, &table->all_set, 1);

	i = 0;
	while (i < table->num_of_philos)
	{
		// join all threads
		safe_thread_op(&(table->philos_arr[i].tid), NULL, NULL, JOIN);
		i++;
	}

	set_val(&table->mtx, &table->end_sim, 1);
	safe_thread_op(&(table->observer), NULL, NULL, JOIN);

	int flag = 0;
	i = 0;
	while (i < table->num_of_philos)
	{
		if (table->philos_arr[i].dead == 1)
		{
			flag = 1;
			break;
		}
		i++;
	}
	if (!flag)	printf("Everyone is full and happy!\nEach had %ld meals\n", table->philos_arr->meal_count);
	
}


int main(int ac, char **av)
{
	if (ac != 6 && ac != 5)
		__exit("Bad args :(\n");

	t_table *table = table_init(ac, av);
	
	__begin(table);
	$t_table(table);
	
	return 0;
}
