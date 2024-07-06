#ifndef INCLUDE_H
#define INCLUDE_H

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>
#include <stdlib.h>

typedef struct s_fork
{
    int                id;
    pthread_mutex_t    lock;

}            t_fork;

typedef struct s_philo
{
    pthread_t          thread;
    int                id;
    long               last_eat;
    int                meal_count;
    int                is_full;
    int                is_dead;
    t_fork             *fork_one;
    t_fork             *fork_two;
    pthread_mutex_t    lock;
    struct s_param     *param;
}                t_philo;

typedef struct s_param
{
    int                 num_philos;
    long                time_die;
    long                time_eat;
    long                time_sleep;
    int                 limit_meals;
    long                start_time;
    int                 all_ready;
    int                 end;
    int                 exit;
    t_philo             *philo;
    t_fork              *fork;
    pthread_mutex_t     lock;
    pthread_mutex_t     print_lock;

}                t_param;

long    ft_atol(char *str);
long    get_lvalue(pthread_mutex_t *lock, long *val);
int     get_value(pthread_mutex_t *lock, int *val);
void    set_lvalue(pthread_mutex_t *lock, long *var, long val);
void    set_value(pthread_mutex_t *lock, int *var, int val);
long    timestamp_in(char c);
void    sleep_for(long ms, t_philo *philo);
void    print_status(t_philo *philo, int status);
void    sleep_for(long ms, t_philo *philo);
void    philo_eat(t_philo *philo);
void    philo_sleep(t_philo *philo);
void    philo_think(t_philo *philo);
int     philo_died(t_philo *philo);

#endif