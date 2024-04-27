/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matoi.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 18:02:58 by aamirkha          #+#    #+#             */
/*   Updated: 2024/04/27 18:25:48 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


static void _skip_whspaces(char const **const str)
{

	while (**str && (**str == ' ' || **str == '\n' || **str == '\t'))
		(*str)++;
}

static int _is_digit(char const c)
{
	return (c >= '0' && c <= '9');
}

static int _is_sign(char const c)
{
	return (c == '+' || c == '-');
}

static long long _process(long long res, char const c)
{
	return ((10 * res) + (c - '0'));
}

int matoi(char const * str)
{
	long long res = 0;
	short sign = 1;

	_skip_whspaces(&str);

	if (_is_sign(*str))
	{
		if (*str == '-')
			sign = -1;
		str++;
	}

	while (*str && _is_digit(*str))
	{
		res = _process(res, *str);
		str++;
	}
	res *= sign;
	if (res > INT_MAX || res < INT_MIN)
		return 0;
	return (int)(res);
}
