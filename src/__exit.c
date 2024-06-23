/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 18:02:29 by aamirkha          #+#    #+#             */
/*   Updated: 2024/06/23 20:56:37 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void __attribute__((noreturn)) __exit(char const * const err)
{
	if (NULL != err)
	{
		printf(RED);
		printf("./philo: %s\n", err);
		printf(RESET);
	}
	exit (EXIT_FAILURE);
}
