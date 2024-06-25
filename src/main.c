/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:34:37 by aamirkha          #+#    #+#             */
/*   Updated: 2024/06/25 14:14:29 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	__log_itog(t_table *table)
{
	bool	flag;
	int		i;
	int		meals;

	meals = table->philos_arr->meal_count;
	flag = false;
	i = 0;
	while (i < table->num_of_philos)
	{
		if (table->philos_arr[i].dead == true)
		{
			flag = true;
			break ;
		}
		i++;
	}
	if (!flag)
	{
		printf(YELLOW);
		printf("Everyone is full and happy!\nEach philo had %ld meals\n",
			table->philos_arr->meal_count);
		printf(RESET);
	}
}

void	*foo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_for_other_philos(philo->table);
	set_val(&philo->table->mtx, &philo->time_last_meal, get_time(MILLISECOND));
	inc_val(&(philo->table->mtx), &(philo->table->active_threads));
	philo_log(TAKE_FORK, philo);
	while (!dinner_finished(philo->table))
		;
	return (NULL);
}

static void	__create_philos(t_table *table)
{
	int	i;

	i = 0;
	if (table->num_of_philos == 1)
	{
		thread_wrapper(&(table->philos_arr[0].tid), foo,
			&(table->philos_arr[0]), CREATE);
	}
	else
	{
		while (i < table->num_of_philos)
		{
			__create(&(table->philos_arr[i].tid), philo_routine,
				&(table->philos_arr[i]));
			i++;
		}
	}
}

void	__begin(t_table *table)
{
	int	i;

	if (has_value(&table->times_each_eat) && value(&table->times_each_eat) == 0)
		return ;
	__create_philos(table);
	__create(&(table->observer), observer_routine, table);
	table->start_sim = get_time(MILLISECOND);
	set_val(&table->mtx, &table->all_set, true);
	i = 0;
	while (i < table->num_of_philos)
	{
		__join(&(table->philos_arr[i].tid));
		i++;
	}
	set_val(&table->mtx, &table->end_sim, true);
	__join(&(table->observer));
	__log_itog(table);
}

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
	system("leaks philo");
}
#endif // __APPLE__
