/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 17:47:17 by aamirkha          #+#    #+#             */
/*   Updated: 2024/04/28 18:35:53 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void forks_destroy(t_table *table)
{
	int i = 0;
	while (i < table->num_of_philos)
	{
		pthread_mutex_destroy(&(table->forks_arr[i].mtx));
		i++;
	}
	free (table->forks_arr);
	table->forks_arr = NULL;
}

void philos_destroy(t_table *table)
{
	// joins maybe

	int i = 0;
	while (i < table->num_of_philos)
	{
		pthread_join(table->philos_arr[i].tid, NULL);
		i++;
	}

	free (table->philos_arr);
	table->philos_arr = NULL;
}

void table_destroy(t_table *table)
{
	philos_destroy(table);
	forks_destroy(table);

	free (table);
	table = NULL;
}
