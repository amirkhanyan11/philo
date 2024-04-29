/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_routine.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:08:02 by aamirkha          #+#    #+#             */
/*   Updated: 2024/04/29 16:06:48 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int someone_dead(t_table * table)
{
	int i = 0;
	while (i < table->num_of_philos)
	{
		if (table->philos_arr[i].dead == 1)
			return 1;
		i++;
	}
	return 0;
}

t_philo *the_most_hungry(t_table * table)
{
	int i = 0;
	t_philo * next_to_eat = table->philos_arr;
	while (i < table->num_of_philos)
	{
		if (table->philos_arr[i].time_last_meal > next_to_eat->time_last_meal)
			next_to_eat = table->philos_arr + i;
		i++;
	}
	return next_to_eat;
}

void *w_routine(void *data)
{
	t_table *table = (t_table*)data;


	t_philo * next_to_eat = the_most_hungry(table);

	next_to_eat->can_i_eat = 1;

	// printf("waiter : the most hungry philo is %d\n", next_to_eat->id);

	return data;
}
