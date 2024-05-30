/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:31:50 by aamirkha          #+#    #+#             */
/*   Updated: 2024/05/30 20:41:46 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <errno.h>
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
typedef struct timeval timeval_t;
typedef struct s_waiter t_waiter;
typedef void *(*t_fptr)(void *);


typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}			t_opcode;

typedef enum e_time_code
{
	SECONDS,
	MILLISECOND = 1e3,
	MICROSECOND = 1e6,
}		t_time_code;

// funcs

int matoi(char const * str);
void forks_init(t_table * table);
t_table *table_init(int ac, char **av);
void philos_init(t_table * table, char **av);
void __exit(char const * const err);
void table_destroy(t_table *table);
void forks_destroy(t_table *table);
void philos_destroy(t_table *table);
void waiter_init(t_table *table);

void	safe_mutex_op(pthread_mutex_t *mutex, t_opcode opcode);
void	safe_thread_op(pthread_t *thread, t_fptr f, void *data, t_opcode opcode);
void	*ft_malloc(size_t n);

void 	*ph_routine(void *data);
void 	*w_routine(void *data);
void	set_val(pthread_mutex_t *mutex, int *dest, int value);
int		get_val(pthread_mutex_t *mutex, int *value);
void	wait4all(t_table *table);
int 	dinner_finished(t_table * table);
void	ft_usleep(int sec);
void	philo_log(t_philo_op opcode, t_philo *philo);


// usr def types

enum
{
	left = 0,
	right = 1
};

typedef enum e_me
{
	EAT,
	SLEEP,
	THINK,
	TAKE_FORK,
	DIE,
}			t_philo_op;

typedef struct s_fork
{
	pthread_mutex_t mtx;
	int id;
	int being_used;
} t_fork;

typedef struct s_philo
{
	pthread_t tid;
	pthread_mutex_t mtx;
	int id;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int time_last_meal;
	int meal_count;
	int full;

	t_table *table;
	int dead;

	t_fork *forks[2];
} t_philo;


typedef struct s_waiter
{
	pthread_t tid;

} t_waiter;

typedef struct s_table
{
	int num_of_philos;
	int times_each_eat; // optional
	int start_sim;
	int end_sim;
	pthread_mutex_t mtx;
	pthread_mutex_t iomtx;


	int all_set; // x

	t_waiter *waiter;
	t_philo *philos_arr;
	t_fork *forks_arr;

} t_table;


#endif // PHILO_H
