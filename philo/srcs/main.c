/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logname <logname@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 09:17:39 by logname           #+#    #+#             */
/*   Updated: 2024/07/06 12:36:04 by logname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/include.h"

int ft_strlen(char *s)
{
    int    i;

    i = 0;
    while (s && s[i])
        ++i;
    return (i);
}

int    ft_isspace(char c)
{
    return ((c >= 7 && c <= 13) || c == 32);
}

// ./philo 5 310 200 200 [10]

void    *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;

    while (get_value(&philo->param->lock, &philo->param->all_ready) == 0)
    ;
    // if (philo->id % 2 != 0)
	// 	sleep_for(philo->param->time_eat - 60, philo);
    while (1)
    {
        philo_eat(philo);
        if (get_value(&philo->param->lock, &philo->param->end) == 1)
            break; ;
        philo_sleep(philo);
        if (get_value(&philo->param->lock, &philo->param->end) == 1)
            break ;
        philo_think(philo);
        if (philo->param->limit_meals != -1
            && philo->meal_count >= philo->param->limit_meals)
            break ;
    }
    return (NULL);
}

int main(int ac, char **av)
{
    t_param     param;
    // int         i;

    if (ac != 5 && ac != 6)
        return (1);
    if (init_param(ac, av, &param))
        return (printf("init_param\n"), 1);
    init_philos(&param);
    // pthread_mutex_destroy(&param.lock);
    // pthread_mutex_destroy(&param.print_lock);
    // i = 0;
    // while (i < param.num_philos)
    // {
    //     pthread_mutex_destroy(&param.philo[i].fork_one->lock);
    //     pthread_mutex_destroy(&param.philo[i].fork_two->lock);
    //     pthread_mutex_destroy(&param.philo[i++].lock);
    // }
    free(param.fork);
    free(param.philo);
    return (0);
}