/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 17:47:17 by aamirkha          #+#    #+#             */
/*   Updated: 2024/06/25 12:36:46 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	__t_fork__(t_fork *fork)
{
	__destroy(&fork->mtx);
}

static void	__t_philo__(t_philo *philo)
{
	__destroy(&philo->mtx);
}

void	__t_table__(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_of_philos)
	{
		__t_philo__(table->philos_arr + i);
		__t_fork__(table->forks_arr + i);
		i++;
	}
	free(table->philos_arr);
	free(table->forks_arr);
	table->philos_arr = NULL;
	table->forks_arr = NULL;
	__destroy(&table->mtx);
	__destroy(&table->iomtx);
	free(table);
	table = NULL;
}
