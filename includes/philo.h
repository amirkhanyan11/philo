/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:31:50 by aamirkha          #+#    #+#             */
/*   Updated: 2024/06/23 20:51:11 by aamirkha         ###   ########.fr       */
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
#include <stdbool.h>
#include <stdarg.h>

#define __number_of_philosophers 1
#define __time_to_die 2
#define __time_to_eat 3
#define __time_to_sleep 4
#define __number_of_times_each_philosopher_must_eat 5

#define PHILO_MAX 200
#define TIME_MIN 100
#define FORK_MAX 2

#define PURPLE "\033[1;35m"
#define CYAN "\033[1;36m"
#define YELLOW "\033[1;33m"
#define RED "\033[1;31m"
#define RESET "\033[0m"


// ./ph number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

typedef struct s_philo t_philo;
typedef struct s_fork t_fork;
typedef struct s_table t_table;
typedef struct timeval t_timeval;
typedef struct s_waiter t_waiter;
typedef struct s_optional t_optional;

typedef pthread_mutex_t t_mutex;
typedef long t_value;

typedef void *(*t_fptr)(void *);
typedef bool (*t_optional_predicate) (const t_optional *obj);


typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
	EAT,
	SLEEP,
	THINK,
	TAKE_FORK,
	DIE
}			t_opcode;

typedef enum e_time_code
{
	SECONDS,
	MILLISECOND = 1000,
	MICROSECOND = 1000000,
}		t_time_code;

enum
{
	left = 0,
	right = 1
};


// funcs

t_optional 		matoi(char const * str);
void 		forks_init(t_table * table);
t_table 	*table_init(int ac, char **av);
void 		philos_init(t_table * table);
void 		forks_destroy(t_table *table);
void 		waiter_init(t_table *table);
void		mutex_wrapper(t_mutex *mutex, t_opcode opcode);
void		thread_wrapper(pthread_t *thread, t_fptr f, void *data, t_opcode opcode);
void 		__lock(t_mutex *mutex);
void 		__unlock(t_mutex *mutex);
void		__attribute__((malloc))	*ft_malloc(size_t n);


void 		*philo_routine(void *data);
void 		*w_routine(void *data);
void		set_val(t_mutex *mutex, t_value *dest, t_value value);
t_value		get_val(t_mutex *mutex, t_value *value);
void		wait4all(t_table *table);
bool 		dinner_finished(t_table * table);
void		ft_usleep(t_value sec, t_table *table);
void		philo_log(t_opcode opcode, t_philo *philo);
t_value 	get_time(t_time_code time_code);
void		*observer_routine(void * data);
void		inc_val(t_mutex *mutex, t_value *val);
int			check_equality(t_mutex *mutex, t_value *lhv, t_value rhv);
void		__mutex_err(int status);
void 		$t_table(t_table *table);

void  		__lock(t_mutex *mutex);
void  		__unlock(t_mutex *mutex);
void  		__init(t_mutex *mutex);
void  		__destroy(t_mutex *mutex);
void  		__create(pthread_t *thread, t_fptr f, void *data);
void  		__join(pthread_t *thread);
void 		__attribute__((unused))   __detach(pthread_t *thread);
void 		__attribute__((noreturn))		__exit(char const * const err);


bool  		has_value(const t_optional *optional);
bool    	has_bad_timeval(const t_optional *optional);
bool 		doesnt_have_value(const t_optional *optional);
t_value 	value(const t_optional *optional);
t_value 	value_or(const t_optional *optional, t_value val);
t_optional 	make_optional();
void 		set_optional(t_optional *optional, t_value val);
bool 		__attribute__((sentinel)) any_of(t_optional_predicate unary_predicate, ...);


struct s_optional
{
	t_value value;
	bool has_value;
};

struct s_fork
{
	t_mutex mtx;
	int id;
};

struct s_philo
{
	pthread_t tid;
	t_mutex mtx;
	t_value id;
	t_value time_last_meal;
	t_value meal_count;
	t_value full;
	t_table *table;
	t_value dead;
	t_fork *forks[FORK_MAX];
};


struct s_table
{
	t_value num_of_philos;
	t_optional times_each_eat; // optional
	t_value start_sim;
	t_value end_sim;
	t_value active_threads;
	t_value time_to_die;
	t_value time_to_eat;
	t_value time_to_sleep;
	t_mutex mtx;
	t_mutex iomtx;
	pthread_t observer;
	t_value all_set; 
	t_philo *philos_arr;
	t_fork *forks_arr;
};


#endif // PHILO_H
