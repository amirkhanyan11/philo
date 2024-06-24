/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:34:37 by aamirkha          #+#    #+#             */
/*   Updated: 2024/06/23 20:52:03 by aamirkha         ###   ########.fr       */
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

	if (has_value(&table->times_each_eat) && value(&table->times_each_eat) == 0) return ;

	if (table->num_of_philos == 1)
	{
		thread_wrapper(&(table->philos_arr[0].tid), foo, &(table->philos_arr[0]), CREATE);
	}

	else
	{
		while (i < table->num_of_philos)
		{
			// create threads
			__create(&(table->philos_arr[i].tid), philo_routine, &(table->philos_arr[i]));
			i++;
		}
	}
	__create(&(table->observer), observer_routine, table);

	table->start_sim = get_time(MILLISECOND);
	
	// notify that all threads are ready
	set_val(&table->mtx, &table->all_set, true);

	i = 0;
	while (i < table->num_of_philos)
	{
		// join all threads
		__join(&(table->philos_arr[i].tid));
		i++;
	}

	set_val(&table->mtx, &table->end_sim, true);
	__join(&(table->observer));

	int flag = false;
	i = 0;
	while (i < table->num_of_philos)
	{
		if (table->philos_arr[i].dead == true)
		{
			flag = true;
			break;
		}
		i++;
	}
	printf(YELLOW);
	if (!flag)	printf("Everyone is full and happy!\nEach had %ld meals\n", table->philos_arr->meal_count);
	printf(RESET);
	
}


int main(int ac, char **av)
{
	if (ac != 6 && ac != 5)
		__exit("Bad argument count");

	t_table *table = table_init(ac, av);
	
	__begin(table);
	
	$t_table(table);
	
	return 0;
}
