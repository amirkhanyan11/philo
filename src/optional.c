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

t_value value(t_optional *optional)
{
    if (has_value(optional)) return optional->value;

    __exit("Bad optional access");
}

t_value value_or(t_optional *optional, t_value val)
{
    if (optional->has_value) return optional->value;

    return val;
}

bool __attribute__((always_inline)) has_value(t_optional *optional)
{
    return optional->has_value;
}