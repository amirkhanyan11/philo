/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 17:47:17 by aamirkha          #+#    #+#             */
/*   Updated: 2024/06/13 13:06:52 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void forks_destroy(t_table *table)
{
	int i = 0;
	while (i < table->num_of_philos)
	{
		safe_mutex_op(&(table->forks_arr[i].mtx), DESTROY);
		i++;
	}
	free (table->forks_arr);
	table->forks_arr = NULL;
}

void philos_destroy(t_table *table)
{
	// joins maybe

	// int i = 0;
	// while (i < table->num_of_philos)
	// {
	// 	safe_thread_op(&(table->philos_arr[i].tid), NULL, NULL, JOIN);
	// 	i++;
	// }

	free (table->philos_arr);
	table->philos_arr = NULL;
}

void table_destroy(t_table *table)
{
	safe_mutex_op(&table->mtx, DESTROY);
	philos_destroy(table);
	forks_destroy(table);

	free (table);
	table = NULL;
}
