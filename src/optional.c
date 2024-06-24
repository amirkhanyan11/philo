/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optional.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 20:03:33 by aamirkha          #+#    #+#             */
/*   Updated: 2024/06/23 21:07:04 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_optional make_optional(void)
{
    t_optional obj;
    obj.has_value = false;
    obj.value = -1;
    return obj;
}

void set_optional(t_optional *optional, t_value val)
{
    optional->value = val;
    optional->has_value = true;
}

t_value value(const t_optional *optional)
{
    if (has_value(optional)) return optional->value;

    __exit("Bad optional access");
}

t_value value_or(const t_optional *optional, t_value val)
{
    if (has_value(optional)) return optional->value;

    return val;
}

bool  has_value(const t_optional *optional)
{
    return optional->has_value;
}

bool doesnt_have_value(const t_optional *optional)
{
    return !has_value(optional);
}

bool    has_bad_timeval(const t_optional *optional)
{
    t_value val = value_or(optional, TIME_MIN - 1);
    return val < TIME_MIN;
}

bool any_of(int argc, t_optional_predicate unary_predicate, ...)
{
    bool res = false;
    t_optional current;

    va_list arglist;
    va_start(arglist, unary_predicate);

    while (argc > 0)
    {
        current = va_arg(arglist, t_optional);
        if (unary_predicate(&current) == true)
        {
            // printf("%d\n", argc);
            res = true;
            break;
        }
        argc--;
    }

    va_end(arglist);
    return res;
}