#include "../include/include.h"

void    *ft_monitor(void *arg)
{
    t_param *param;
    int     i;
    int     j;

    param = (t_param *)arg;
    while (get_value(&param->lock, &param->all_ready) == 0)
        ;
    sleep_for(get_lvalue(&param->lock, &param->time_die),  NULL);
    j = get_value(&param->lock, &param->num_philos);
    while (!get_value(&param->lock, &param->end))
    {
        i = 0;
        while (i < j)
        {
            if (philo_died(&param->philo[i++]))
                break ;
        }
    }
    return (NULL);
}

void    init_philos(t_param *param)
{
    int i;

    i = 0;
    while (i < param->num_philos)
    {
        init_fork(param, i);
        init_philo_val(param, i);
        ++i;
    }
    i = 0;
    while (i < param->num_philos)
    {
        pthread_create(&param->philo[i].thread, NULL, routine, &param->philo[i]);
        ++i;
    }

    pthread_create(&param->monitor, NULL, ft_monitor, param);

    set_lvalue(&param->lock, &param->start_time, timestamp_in('m'));
    set_value(&param->lock, &param->all_ready, 1);
    i = 0;
    while (i < param->num_philos)
        pthread_join(param->philo[i++].thread, NULL);
    pthread_join(param->monitor, NULL);
}

int init_fork(t_param *param, int i)
{
    param->fork[i].id = i;
    if (pthread_mutex_init(&param->fork[i].lock, NULL))
        return (printf("mutex init fork\n"), 1);
    return (0);
}


int    init_philo_val(t_param *param, int i)
{
    param->philo[i].id = i + 1;
    param->philo[i].last_eat = 0;
    param->philo[i].meal_count = 0;
    param->philo[i].is_full = 0;
    param->philo[i].is_dead = 0;
    if (pthread_mutex_init(&param->philo[i].lock, NULL))
        return (printf("init philo mutex\n"), 1);
    param->philo[i].param = param;
    param->philo[i].fork_one = &param->fork[(i + 1) % param->num_philos];
    param->philo[i].fork_two = &param->fork[i];
    if (param->philo[i].id % 2)
    {
        param->philo[i].fork_one = &param->fork[i];
        param->philo[i].fork_two = &param->fork[(i + 1) % param->num_philos];
    }
    return (0);
}

int    init_param(int ac, char **av, t_param *param)
{
    if (ft_atol(av[1]) <= 0 || ft_atol(av[2]) <= 0
        || ft_atol(av[3]) <= 0 || ft_atol(av[4]) <= 0)
        return (1);
    if (ac == 6 && ft_atol(av[5]) <= 0)
        return (1);
    param->num_philos = ft_atol(av[1]);
    param->time_die = ft_atol(av[2]);
    param->time_eat = ft_atol(av[3]);
    param->time_sleep = ft_atol(av[4]);
    param->limit_meals = -1;
    param->all_ready = 0;
    param->end = 0;
    param->exit = 0;
    if (ac == 6)
        param->limit_meals = ft_atol(av[5]);
    if (pthread_mutex_init(&param->lock, NULL))
        return (1);
    param->philo = (t_philo *) malloc((param->num_philos) * sizeof(t_philo));
    param->fork = (t_fork *) malloc((param->num_philos) * sizeof(t_fork));
    if (!param->fork || !param->philo)
        return (printf("if (!param->fork || !param->philo)\n"),
        free(param->fork), free(param->philo), 1);
    if (pthread_mutex_init(&param->lock, NULL) || pthread_mutex_init(&param->print_lock, NULL)
        || pthread_mutex_init(&param->monitor_lock, NULL))
        return (printf("mutex init print lock"), 1);
    return (0);
}