/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 17:47:17 by aamirkha          #+#    #+#             */
/*   Updated: 2024/06/23 20:14:58 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


static void __attribute__((always_inline)) $t_fork(t_fork *fork)
{
	__destroy(&fork->mtx);
}


static void __attribute__((always_inline)) $t_philo(t_philo *philo)
{
	__destroy(&philo->mtx);
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
	
	__destroy(&table->mtx);
	__destroy(&table->iomtx);

	free (table);
	table = NULL;
}
