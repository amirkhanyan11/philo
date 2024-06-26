/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 18:02:58 by aamirkha          #+#    #+#             */
/*   Updated: 2024/06/26 20:48:10 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

inline void __attribute__((always_inline))	___death(t_table *table)
{
	free (table);
	__exit("Bad argument values", __scary_error_info__);
}

void	__init__minit(t_table *table, char **av)
{
	t_optional	num_of_philos;
	t_optional	time_to_die;
	t_optional	time_to_eat;
	t_optional	time_to_sleep;

	num_of_philos = matoi(av[__NUMBER_OF_PHILOSOPHERS]);
	time_to_die = matoi(av[__TIME_TO_DIE]);
	time_to_eat = matoi(av[__TIME_TO_EAT]);
	time_to_sleep = matoi(av[__TIME_TO_SLEEP]);
	if (any_of(doesnt_have_value, &num_of_philos, &time_to_die, &time_to_sleep,
			&time_to_eat, NULL) || any_of(has_bad_timeval, &time_to_die,
			&time_to_sleep, &time_to_eat, NULL) || value(&num_of_philos) < 1
		|| value(&num_of_philos) > PHILO_MAX)
	{
		___death(table);
	}
	table->num_of_philos = value(&num_of_philos);
	table->time_to_die = value(&time_to_die) * MILLISECOND;
	table->time_to_eat = value(&time_to_eat) * MILLISECOND;
	table->time_to_sleep = value(&time_to_sleep) * MILLISECOND;
}

t_table	*table_init(int ac, char **av)
{
	t_table		*table;
	t_optional	times_each_eat;

	table = ft_malloc(sizeof(t_table));
	// __exit("o novu");
	__init__minit(table, av);
	if (ac == 6)
	{
		times_each_eat = matoi(av[__NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT]);
		set_optional(&table->times_each_eat, value(&times_each_eat));
		if (value(&times_each_eat) < 0)
			___death(table);
	}
	else
		table->times_each_eat = make_optional();
	table->end_sim = false;
	table->all_set = false;
	table->start_sim = 0;
	table->active_threads = 0;
	__init(&table->mtx);
	__init(&table->iomtx);
	forks_init(table);
	philos_init(table);
	return (table);
}

void	philos_init(t_table *table)
{
	int	i;

	table->philos_arr = ft_malloc(sizeof(t_philo) * table->num_of_philos);
	i = 0;
	while (i < table->num_of_philos)
	{
		table->philos_arr[i].id = i + 1;
		table->philos_arr[i].forks[left] = &(table->forks_arr[i]);
		table->philos_arr[i].forks[right] = &(table->forks_arr[(i + 1) % table->num_of_philos]);
		__init(&(table->philos_arr[i].mtx));
		table->philos_arr[i].time_last_meal = 0;
		table->philos_arr[i].dead = 0;
		table->philos_arr[i].full = 0;
		table->philos_arr[i].meal_count = 0;
		table->philos_arr[i].table = table;
		i++;
	}
}

void	forks_init(t_table *table)
{
	int	i;

	table->forks_arr = ft_malloc(sizeof(t_fork) * table->num_of_philos);
	i = 0;
	while (i < table->num_of_philos)
	{
		__init(&(table->forks_arr[i].mtx));
		table->forks_arr[i].id = i + 1;
		i++;
	}
}
