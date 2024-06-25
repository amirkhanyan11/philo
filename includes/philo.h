/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:31:50 by aamirkha          #+#    #+#             */
/*   Updated: 2024/06/25 15:55:33 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <cocobolo.h>
# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define __NUMBER_OF_PHILOSOPHERS 1
# define __TIME_TO_DIE 2
# define __TIME_TO_EAT 3
# define __TIME_TO_SLEEP 4
# define __NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT 5

# define PHILO_MAX 200
# define TIME_MIN 60
# define FORK_MAX 2

typedef struct s_philo	t_philo;
typedef struct s_fork	t_fork;
typedef struct s_table	t_table;
typedef struct timeval	t_timeval;

typedef pthread_mutex_t	t_mutex;
typedef long			t_value;

typedef void			*(*t_fptr)(void *);

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
}						t_opcode;

typedef enum e_time_code
{
	SECONDS,
	MILLISECOND = 1000,
	MICROSECOND = 1000000,
}						t_time_code;

enum
{
	left = 0,
	right = 1
};

void					forks_init(t_table *table);
void					philos_init(t_table *table);
void					forks_destroy(t_table *table);
void					waiter_init(t_table *table);
void					__lock(t_mutex *mutex);
void					__unlock(t_mutex *mutex);
void					*ft_malloc(size_t n) __attribute__((malloc));
void					*philo_routine(void *data);
void					*w_routine(void *data);
void					set_val(t_mutex *mutex, t_value *dest, t_value value);
void					wait_for_other_philos(t_table *table);
void					ft_usleep(t_value sec, t_table *table);
void					philo_log(t_opcode opcode, t_philo *philo);
void					*observer_routine(void *data);
void					inc_val(t_mutex *mutex, t_value *val);
void					__mutex_err(int status);
void					__t_table__(t_table *table);
void					__lock(t_mutex *mutex);
void					__unlock(t_mutex *mutex);
void					__init(t_mutex *mutex);
void					__destroy(t_mutex *mutex);
void					__create(pthread_t *thread, t_fptr f, void *data);
void					__join(pthread_t *thread);
void					__detach(pthread_t *thread) __attribute__((unused));
void					__begin(t_table *table);

t_value					get_val(t_mutex *mutex, t_value *value);
t_value					get_time(t_time_code time_code);
t_table					*table_init(int ac, char **av);

bool					has_bad_timeval(const t_optional *optional);
bool					dinner_finished(t_table *table);
bool					doesnt_have_value(const t_optional *optional);
bool					check_equality(t_mutex *mutex, t_value *lhv,
							t_value rhv);
bool					is_dead(t_philo *philo);

struct					s_fork
{
	t_mutex				mtx;
	int					id;
};

struct					s_philo
{
	pthread_t			tid;
	t_mutex				mtx;
	t_value				id;
	t_value				time_last_meal;
	t_value				meal_count;
	t_value				full;
	t_table				*table;
	t_value				dead;
	t_fork				*forks[FORK_MAX];
};

struct					s_table
{
	t_value				num_of_philos;
	t_optional			times_each_eat;
	t_value				start_sim;
	t_value				end_sim;
	t_value				active_threads;
	t_value				time_to_die;
	t_value				time_to_eat;
	t_value				time_to_sleep;
	t_mutex				mtx;
	t_mutex				iomtx;
	pthread_t			observer;
	t_value				all_set;
	t_philo				*philos_arr;
	t_fork				*forks_arr;
};

#endif // PHILO_H
