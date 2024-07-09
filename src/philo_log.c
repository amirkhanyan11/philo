/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:14:33 by aamirkha          #+#    #+#             */
/*   Updated: 2024/06/29 17:42:53 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

inline void	__attribute__((always_inline))	__log__eat(t_philo *philo)
{
	printf(CYAN);
	printf("%ld %ld is eating\n", get_time(MILLISECOND)
		- philo->table->start_sim, philo->id);
	printf(RESET);
}

inline void	__attribute__((always_inline))	__log__die(t_philo *philo)
{
	printf(RED);
	printf("%ld %ld died\n", get_time(MILLISECOND) - philo->table->start_sim,
		philo->id);
	printf(RESET);
}

void	philo_log(t_opcode opcode, t_philo *philo)
{
	__lock(&(philo->table->iomtx));
	if (!dinner_finished(philo->table))
	{
		if (TAKE_FORK == opcode)
			printf("%ld %ld has taken a fork\n", get_time(MILLISECOND)
				- philo->table->start_sim, philo->id);
		else if (EAT == opcode)
			__log__eat(philo);
		else if (SLEEP == opcode)
			printf("%ld %ld is sleeping\n", get_time(MILLISECOND)
				- philo->table->start_sim, philo->id);
		else if (THINK == opcode)
			printf("%ld %ld is thinking\n", get_time(MILLISECOND)
				- philo->table->start_sim, philo->id);
		else if (DIE == opcode)
			__log__die(philo);
	}
	__unlock(&(philo->table->iomtx));
}
