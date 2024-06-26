/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:33:23 by aamirkha          #+#    #+#             */
/*   Updated: 2024/06/26 17:10:34 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	__log_itog(t_table *table)
{
	bool	flag;
	int		i;

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

static void	*foo(void *data)
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
		__create(&(table->philos_arr[0].tid), foo, &(table->philos_arr[0]));
	}
	else
	{
		while (i < table->num_of_philos)
		{
			__create(&(table->philos_arr[i].tid), philo_routine, &(table->philos_arr[i]));
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

	__create(&(table->sentinel), sentinel_routine, table);

	table->start_sim = get_time(MILLISECOND);

	set_val(&table->mtx, &table->all_set, true);	

	i = 0;
	while (i < table->num_of_philos)
	{
		__join(&(table->philos_arr[i].tid));
		i++;
	}
	set_val(&table->mtx, &table->end_sim, true);
	__join(&(table->sentinel));
	__log_itog(table);
}
