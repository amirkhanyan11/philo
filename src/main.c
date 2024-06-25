/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:34:37 by aamirkha          #+#    #+#             */
/*   Updated: 2024/06/25 20:44:46 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	*table;

	if (ac != 6 && ac != 5)
		__exit("Bad argument count");
	table = table_init(ac, av);
	__begin(table);
	__t_table__(table);
	return (0);
}

#ifdef __APPLE__
void	__attribute__((destructor)) moid(void)
{
	printf(GREEN);
	printf("\n\nLeaks report\n");
	system("leaks philo");
	printf(RESET);
}
#endif // __APPLE__
