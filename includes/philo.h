/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:31:50 by aamirkha          #+#    #+#             */
/*   Updated: 2024/06/23 18:18:20 by aamirkha         ###   ########.fr       */
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

#define PURPLE "\033[1;35m"
#define CYAN "\033[1;36m"
#define GREEN "\033[1;33m"
#define RED "\033[1;31m"
#define RESET "\033[0m"


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
	MILLISECOND = 1000,
	MICROSECOND = 1000000,
}		t_time_code;

typedef enum e_me
{
	EAT,
	SLEEP,
	THINK,
	TAKE_FORK,
	DIE,
}			t_philo_op;


enum
{
	left = 0,
	right = 1
};



// funcs

int 	matoi(char const * str);
void 	forks_init(t_table * table);
t_table *table_init(int ac, char **av);
void 	philos_init(t_table * table);
void 	__exit(char const * const err);
void 	forks_destroy(t_table *table);
void 	waiter_init(t_table *table);

void	safe_mutex_op(pthread_mutex_t *mutex, t_opcode opcode);
void	safe_thread_op(pthread_t *thread, t_fptr f, void *data, t_opcode opcode);
void	*ft_malloc(size_t n);
void 	__lock(pthread_mutex_t *mutex);
void 	__unlock(pthread_mutex_t *mutex);


void 	*philo_routine(void *data);
void 	*w_routine(void *data);
void	set_val(pthread_mutex_t *mutex, long *dest, long value);
long	get_val(pthread_mutex_t *mutex, long *value);
void	wait4all(t_table *table);
int 	dinner_finished(t_table * table);
void	ft_usleep(long sec, t_table *table);
void	philo_log(t_philo_op opcode, t_philo *philo);
long 	get_time(t_time_code time_code);
void	*observer_routine(void * data);
void	inc_val(pthread_mutex_t *mutex, long *val);
int		check_equality(pthread_mutex_t *mutex, long *lhv, long rhv);

void 	$t_table(t_table *table);


typedef struct s_fork
{
	pthread_mutex_t mtx;
	int id;
} t_fork;

typedef struct s_philo
{
	pthread_t tid;
	pthread_mutex_t mtx;
	int id;

	long time_last_meal;
	long meal_count;
	long full;

	t_table *table;
	long dead;

	t_fork *forks[2];
}	t_philo;


typedef struct s_table
{
	long num_of_philos;
	long times_each_eat; // optional
	long start_sim;
	long end_sim;
	long active_threads;

	long time_to_die;
	long time_to_eat;
	long time_to_sleep;
	
	pthread_mutex_t mtx;
	pthread_mutex_t iomtx;
	pthread_t observer;


	long all_set; // x

	t_waiter *waiter;
	t_philo *philos_arr;
	t_fork *forks_arr;

} t_table;


#endif // PHILO_H
