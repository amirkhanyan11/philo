/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:31:50 by aamirkha          #+#    #+#             */
/*   Updated: 2024/04/27 18:31:20 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <sys/time.h>

#define bad_value LONG_MAX
#define __number_of_philosophers 1
#define __time_to_die 2
#define __time_to_eat 3
#define __time_to_sleep 4
#define __number_of_times_each_philosopher_must_eat 5

// ./ph number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

typedef struct s_philo t_philo;
typedef struct s_fork t_fork;
typedef struct s_table t_table;



// funcs

int matoi(char const * str);



// usr def types

enum
{
	LEFT = 0,
	RIGHT
};

typedef struct s_fork
{
	pthread_mutex_t mtx;
	short num;
} t_fork;

typedef struct s_philo
{
	pthread_t tid;
	short eating;
	short thinking;
	short sleeping;
	short dead;
	t_fork *forks[2];

} t_philo;

typedef struct s_table
{
	short num_of_philos;
	short time_to_die;
	short time_to_eat;
	short time_to_sleep;
	short times_each_eat; // optional

	t_philo *philos_arr;


} t_table;


#endif // PHILO_H
