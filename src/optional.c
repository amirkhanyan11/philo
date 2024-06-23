/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optional.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 20:03:33 by aamirkha          #+#    #+#             */
/*   Updated: 2024/06/23 20:05:13 by aamirkha         ###   ########.fr       */
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