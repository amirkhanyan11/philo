/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:38:48 by aamirkha          #+#    #+#             */
/*   Updated: 2024/07/09 17:57:01 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_for_other_philos(t_table *table)
{
	while (true != get_val(&(table->mtx), &(table->all_set)));
}

void	sentinel_wait(t_table *table)
{
	while (false == check_equality(&table->mtx, &table->active_threads,
			table->num_of_philos))
		;
}

void	__jetlag(t_philo *philo)
{
	t_value	t;

	t = philo->table->time_to_eat * __SUPER__SECRET__PROPORTION__ - philo->table->time_to_sleep;
	if (t > 0)
	{
		ft_usleep(t / __SUPER__SECRET__PROPORTION__, philo->table);
	}
}
