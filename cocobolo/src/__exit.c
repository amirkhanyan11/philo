/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 18:02:29 by aamirkha          #+#    #+#             */
/*   Updated: 2024/06/26 20:49:15 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cocobolo.h>


void	__attribute__((noreturn)) __attribute__((sentinel)) __exit(const char * const err, ...)
{
	va_list args;

	va_start(args, err);

	const char *file = va_arg(args, char *);
	const char *function = va_arg(args, char *);
	int line = va_arg(args, int);


	if (NULL != err)
	{
		printf(RED);
		printf("\n./philo: %s\n\n", err);

		if (file)
			printf("file 	  :   %s\n"
				   "function  :   %s\n"
					"line 	  :   %d\n\n", file, function, line);

		printf(RESET);
	}
	va_end(args);

	exit(EXIT_FAILURE);
}

