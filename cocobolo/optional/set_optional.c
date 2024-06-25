/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_optional.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:17:46 by aamirkha          #+#    #+#             */
/*   Updated: 2024/06/25 13:20:27 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cocobolo.h"

void	set_optional(t_optional *optional, t_value val)
{
	optional->value = val;
	optional->has_value = true;
}
