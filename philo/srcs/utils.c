
#include "../include/include.h"

int ft_isdigit(char c)
{
    return (c >= '0' && c <= '9');
}

long    ft_atol(char *str)
{
    long    num;
    int             i;

    i = 0;
    num = 0;
    while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
        i++;
    if (str[i] == '+' || str[i] == '-')
    {
        if (str[i] == '-')
            return (-1);
        ++i;
    }
    while (ft_isdigit(str[i]))
    {
        num = num * 10 + str[i] - '0';
        ++i;
    }
    if (num > INT_MAX || num < 0)
        return (-1);
    return (num);
}

long    timestamp_in(char c)
{
    struct timeval  tv;
    long            ret;
    
    gettimeofday(&tv, NULL);
    if (c == 'u')
        ret = tv.tv_usec + tv.tv_sec * 1000000;
    else
        ret = tv.tv_usec / 1000 + tv.tv_sec * 1000;
    return (ret);
}

int philo_died(t_philo *philo)
{
    if (philo->meal_count == 0)
    {
        if ((timestamp_in('m') - get_lvalue(&philo->param->lock, &philo->param->start_time))
            >= philo->param->time_die)
        {
            print_status(philo, 0);
            return (1);
        }
    }
    else
    {
        if (timestamp_in('m') - philo->last_eat >= philo->param->time_die)
        {
            print_status(philo, 0);
            return (1);
        }
    }
    return (0);
}