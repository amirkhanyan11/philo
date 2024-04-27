/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 18:02:58 by aamirkha          #+#    #+#             */
/*   Updated: 2024/04/27 18:38:03 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int _is_correct_table(t_table *table)
{
	return (table->num_of_philos && table->time_to_die && table->time_to_eat && table->time_to_sleep && table->times_each_eat);
}

t_table *table_init(int ac, char **av)
{
	t_table *table = malloc (sizeof(t_table));

	table->num_of_philos = matoi(av[__number_of_philosophers]);
	table->time_to_die = matoi(av[__time_to_die]);
	table->time_to_eat = matoi(av[__time_to_eat]);
	table->time_to_sleep = matoi(av[__time_to_sleep]);
	if (ac == 6)
		table->times_each_eat = matoi(av[__number_of_times_each_philosopher_must_eat]);
	else
		table->times_each_eat = -1;

	if (!_is_correct_table(table))
		__exit("Bad args :(\n");

	table->philos_arr = malloc (sizeof(t_philo) * table->num_of_philos);
	
}
