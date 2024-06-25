/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:58:31 by aamirkha          #+#    #+#             */
/*   Updated: 2024/06/25 12:37:04 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_value	get_time(t_time_code time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		__exit("Bad time");
	if (MILLISECOND == time_code)
		return (tv.tv_sec * MILLISECOND + tv.tv_usec / MILLISECOND);
	else if (MICROSECOND == time_code)
		return (tv.tv_sec * MICROSECOND + tv.tv_usec);
	else if (SECONDS == time_code)
		return (tv.tv_sec + tv.tv_usec / MICROSECOND);
	else
		__exit("Bad time");
	return (-1);
}

void	ft_usleep(t_value sec, t_table *table)
{
	t_value	start;

	start = get_time(MICROSECOND);
	while (sec > (get_time(MICROSECOND) - start) && !dinner_finished(table))
		;
}
