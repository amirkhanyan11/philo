/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:15:04 by aamirkha          #+#    #+#             */
/*   Updated: 2024/06/25 13:19:21 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*observer_routine(void *data)
{
	t_table	*table;
	int		i;

	table = (t_table *)data;
	while (0 == check_equality(&table->mtx, &table->active_threads,
			table->num_of_philos))
		;
	while (!dinner_finished(table))
	{
		i = 0;
		while (i < table->num_of_philos && !dinner_finished(table))
		{
			if (is_dead(table->philos_arr + i))
			{
				philo_log(DIE, &table->philos_arr[i]);
				set_val(&table->mtx, &table->end_sim, true);
				set_val(&table->mtx, &table->philos_arr[i].dead, true);
			}
			i++;
		}
	}
	return (data);
}
