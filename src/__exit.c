/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 18:02:29 by aamirkha          #+#    #+#             */
/*   Updated: 2024/05/13 17:11:57 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void __exit(char const * const err)
{
	if (NULL != err)
		printf("./philo: %s\n", err);
	exit (EXIT_FAILURE);
}
