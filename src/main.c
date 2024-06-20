/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:34:37 by aamirkha          #+#    #+#             */
/*   Updated: 2024/06/20 15:32:33 by aamirkha         ###   ########.fr       */
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

	if (table->num_of_philos == 1)
	{
		safe_thread_op(&(table->philos_arr[0].tid), foo, &(table->philos_arr[0]), CREATE);
	}

	else
	{
		while (i < table->num_of_philos)
		{
			// create threads
			safe_thread_op(&(table->philos_arr[i].tid), ph_routine, &(table->philos_arr[i]), CREATE);
			i++;
		}
	}



	// notify that all threads are ready
	set_val(&table->mtx, &table->start_sim, get_time(MILLISECOND));
	set_val(&table->mtx, &table->all_set, 1);
	safe_thread_op(&(table->observer), ob_routine, table, CREATE);

	// printf ("time mime : %ld\n", get_time(MILLISECOND) - get_val(&table->mtx, &table->start_sim));


	i = 0;
	while (i < table->num_of_philos)
	{
		// join all threads
		safe_thread_op(&(table->philos_arr[i++].tid), NULL, NULL, JOIN);
	}

	set_val(&table->mtx, &table->end_sim, 1);
	safe_thread_op(&(table->observer), NULL, NULL, JOIN);

	// printf("Everyone is full and happy!\n");

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
