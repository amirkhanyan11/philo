/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_optional.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:08:16 by aamirkha          #+#    #+#             */
/*   Updated: 2024/06/25 12:19:52 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cocobolo.h"

t_optional	make_optional(void)
{
	t_optional	obj;

	obj.has_value = false;
	obj.value = 0;
	return (obj);
}
