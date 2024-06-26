/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:58:31 by aamirkha          #+#    #+#             */
/*   Updated: 2024/06/26 20:43:07 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_value	get_time(t_time_code time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		__exit("Bad time", __scary_error_info__);
	if (MILLISECOND == time_code)
		return (tv.tv_sec * MILLISECOND + tv.tv_usec / MILLISECOND);
	else if (MICROSECOND == time_code)
		return (tv.tv_sec * MICROSECOND + tv.tv_usec);
	else
		__exit("Bad time", __scary_error_info__);
	return (-1);
}

// void	ft_usleep(long usec, t_table *table)
// {
// 	long	asleep;
// 	long	spent;
// 	long	left;

// 	spent = 0;
// 	asleep = ft_gettm(USEC);
// 	while (spent < usec)
// 	{
// 		if (dinner_finished(table) == true)
// 			break ;
// 		spent = ft_gettm(USEC) - asleep;
// 		left = usec - spent;
// 		if (left > 1000)
// 			usleep(left / 2);
// 		else
// 		{
// 			while (ft_gettm(USEC) - asleep < usec)
// 				;
// 		}
// 	}
// }


// void	ft_usleep(t_value sec, t_table *table)
// {
// 	t_value	asleep;
// 	t_value	spent;
// 	t_value	left;


// 	spent = 0;
// 	asleep = get_time(MICROSECOND);
// 	while (spent < sec && !dinner_finished(table))
// 	{
// 		spent = get_time(MICROSECOND) - asleep;
// 		left = sec - spent;
// 		if (left > MICROSECOND) usleep(left / 2);
		
// 		else 	while (sec > (get_time(MICROSECOND) - asleep) && !dinner_finished(table)); 
// 	}


// }




void	ft_usleep(t_value sec, t_table *table)
{
	t_value	start;

	start = get_time(MICROSECOND);
	while (sec > (get_time(MICROSECOND) - start) && !dinner_finished(table))
		;
}
