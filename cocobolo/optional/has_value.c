/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:18:41 by aamirkha          #+#    #+#             */
/*   Updated: 2024/06/25 12:19:50 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cocobolo.h"

bool	has_value(const t_optional *optional)
{
	return (optional->has_value);
}
