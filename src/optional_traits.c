/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optional_traits.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:46:53 by aamirkha          #+#    #+#             */
/*   Updated: 2024/06/25 11:02:34 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
