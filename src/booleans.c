/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   booleans.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:18:58 by aamirkha          #+#    #+#             */
/*   Updated: 2024/07/04 16:37:13 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_dead(t_philo *philo)
{
	t_value	elapsed;

	if (get_val(&philo->mtx, &(philo->full)) == true)
		return (false);
	elapsed = get_time(MILLISECOND) - get_val(&philo->mtx, &(philo->time_last_meal));

	return (elapsed > (philo->table->time_to_die / MILLISECOND));
}

bool	check_equality(t_mutex *mutex, t_value *lhv, t_value rhv)
{
	bool	res;

	__lock(mutex);
	res = (*lhv == rhv);
	__unlock(mutex);
	return (res);
}

bool	dinner_finished(t_table *table)
{
	return (get_val(&(table->mtx), &(table->end_sim)));
}

bool	doesnt_have_value(const t_optional *optional)
{
	return (!has_value(optional));
}

bool	has_bad_timeval(const t_optional *optional)
{
	t_value	val;

	val = value_or(optional, TIME_MIN - 1);
	return (val < TIME_MIN);
}
