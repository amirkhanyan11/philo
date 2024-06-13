/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:34:37 by aamirkha          #+#    #+#             */
/*   Updated: 2024/06/13 12:53:39 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



void __begin(t_table * table)
{
	int i = 0;
	while (i < table->num_of_philos)
	{
		// create threads
		safe_thread_op(&(table->philos_arr[i].tid), ph_routine, &(table->philos_arr[i]), CREATE);
		i++;
	}

	// notify that all threads are ready
	table->start_sim = get_time(MILLISECOND);
	set_val(&table->mtx, &table->all_set, 1);

	i = 0;
	while (i < table->num_of_philos)
	{
		// join all threads
		safe_thread_op(&(table->philos_arr[i++].tid), NULL, NULL, JOIN);
	}
}


int main(int ac, char **av)
{
	if (ac != 6 && ac != 5)
		__exit("Bad args :(\n");

	t_table *table = table_init(ac, av);

	// for (int i = 0; i < table->num_of_philos; i++)
	// {
	// 	t_philo *current = &(table->philos_arr[i]);
	// 	printf ("forks of philo %d -> left %d & right %d\n", current->id, current->forks[left]->id, current->forks[right]->id);
	// }

	__begin(table);

	table_destroy(table);
	return 0;
}
