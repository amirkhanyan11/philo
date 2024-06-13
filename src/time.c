/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:58:31 by aamirkha          #+#    #+#             */
/*   Updated: 2024/06/13 12:58:19 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int get_time(t_time_code time_code)
{
	struct timeval tv;
	if (gettimeofday(&tv, NULL) != 0)
		__exit("Bad time");
	if (MILLISECOND == time_code)
		return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	else if (MICROSECOND == time_code)
		return (tv.tv_sec * 1000000 + tv.tv_usec);
	else if (SECONDS == time_code)
		return (tv.tv_sec + tv.tv_usec / 1000000);
	else
		__exit("Bad time");
	return -1;
}

void	ft_usleep(int sec, t_table *table)
{
	int	start;

	start = get_time(MICROSECOND);
	while (sec > (get_time(MICROSECOND) - start) && !dinner_finished(table))
	{
		if (sec - get_time(MICROSECOND) + start > MILLISECOND)
			usleep(sec / 2);
		else
		{
			while(sec > (get_time(MICROSECOND) - start));
		}
	}

}




