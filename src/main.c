/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:34:37 by aamirkha          #+#    #+#             */
/*   Updated: 2024/04/27 19:39:53 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int main(int ac, char **av)
{
	if (ac != 6 && ac != 5)
		__exit("Bad args :(\n");

	t_table *table = table_init(ac, av);

	for (int i = 0; i < table->num_of_philos; i++)
	{
		t_philo *current = &(table->philos_arr[i]);
		printf ("forks of philo %d -> left %d & right %d\n", current->id, current->forks[left]->id, current->forks[right]->id);
	}
	return 0;
}
