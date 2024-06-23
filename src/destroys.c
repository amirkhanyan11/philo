/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 17:47:17 by aamirkha          #+#    #+#             */
/*   Updated: 2024/06/23 17:03:00 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


static void __attribute__((always_inline)) $t_fork(t_fork *fork)
{
	safe_mutex_op(&fork->mtx, DESTROY);
}


static void __attribute__((always_inline)) $t_philo(t_philo *philo)
{
	safe_mutex_op(&philo->mtx, DESTROY);
}

void $t_table(t_table *table)
{
	int i = 0;
	while (i < table->num_of_philos)
	{
		$t_philo(table->philos_arr + i);
		$t_fork(table->forks_arr + i);
		i++;
	}
	
	free (table->philos_arr);
	free (table->forks_arr);
	table->philos_arr = NULL;
	table->forks_arr = NULL;
	
	safe_mutex_op(&table->mtx, DESTROY);
	safe_mutex_op(&table->iomtx, DESTROY);

	free (table);
	table = NULL;
}
