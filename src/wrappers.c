/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:20:23 by aamirkha          #+#    #+#             */
/*   Updated: 2024/05/13 14:29:53 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



void	*ft_malloc(size_t n)
{
	void	*ptr;

	ptr = malloc(n);
	if (NULL == ptr)
		error_exit("Error with the malloc");
	return (ptr);
}
