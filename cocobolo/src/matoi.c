/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matoi.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 18:02:58 by aamirkha          #+#    #+#             */
/*   Updated: 2024/06/25 12:23:52 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cocobolo.h"

static void _skip_spaces(char const **const str)
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

t_optional matoi(char const * str)
{
	long long num = 0;
	short sign = 1;
	t_optional res = make_optional();

	_skip_spaces(&str);

	if (_is_sign(*str))
	{
		if (*str == '-')
			sign = -1;
		str++;
	}

	while (*str && _is_digit(*str))
	{
		num = _process(num, *str);
		str++;
	}
	num *= sign;
	set_optional(&res, num);
	if (num > INT_MAX || num < INT_MIN)
		return make_optional();
	return res;
}
