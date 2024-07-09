/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 18:02:29 by aamirkha          #+#    #+#             */
/*   Updated: 2024/06/29 17:37:56 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cocobolo.h>

void	__attribute__((noreturn))	__exit(const char *const err)
{
	if (NULL != err)
	{
		printf(RED);
		printf("\n./philo: %s\n\n", err);
		printf(RESET);
	}
	exit(EXIT_FAILURE);
}
