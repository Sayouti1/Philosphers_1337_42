#include "../include/include.h"

void print_status(t_philo *philo, int status)
{
    long time;

    pthread_mutex_lock(&philo->param->print_lock);
    time = (timestamp_in('m') - get_lvalue(&philo->param->lock, &philo->param->start_time));
    if (status == 0)
    {
        set_value(&philo->param->lock, &philo->param->end, 1);
        if (get_value(&philo->param->lock, &philo->param->exit) == 0)
            printf("%ld %d died\n", time, philo->id);
        set_value(&philo->param->lock, &philo->param->exit, 1);
    }
    else if (status == 1 && !get_value(&philo->param->lock, &philo->param->end))
             printf("%ld %d has taken a fork\n", time, philo->id);
    else if (status == 2 && !get_value(&philo->param->lock, &philo->param->end))
             printf("%ld %d is eating\n", time, philo->id);
    else if (status == 3 && !get_value(&philo->param->lock, &philo->param->end))
             printf("%ld %d is sleeping\n", time, philo->id);
    else if (status == 4 && !get_value(&philo->param->lock, &philo->param->end))
             printf("%ld %d is thinking\n", time, philo->id);
    pthread_mutex_unlock(&philo->param->print_lock);
}

void    sleep_for(long ms, t_philo *philo)
{
        long    now;
        long    elapsed;
        long    rem;

        now = timestamp_in('u');
        ms *= 1000;
        if (philo_died(philo))
            return ;
        while (timestamp_in('u') - now < ms)
        {
                if (philo_died(philo))
                        return ;
                elapsed = timestamp_in('u') - now;
                rem = ms - elapsed;
                if (rem > 1000)
                        usleep((rem) / 2);
                if (get_value(&philo->param->lock, &philo->param->end))
                        return ;
        }
}


void    philo_eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->fork_one->lock);
    print_status(philo, 1);
    
    if (get_value(&philo->param->lock, &philo->param->end) == 1)
    {
         pthread_mutex_unlock(&philo->fork_one->lock);
        return ;
    }
    pthread_mutex_lock(&philo->fork_two->lock);
    print_status(philo, 1);

    print_status(philo, 2);
    set_lvalue(&philo->lock, &philo->last_eat, timestamp_in('m'));
    sleep_for(philo->param->time_eat, philo);
    pthread_mutex_unlock(&philo->fork_one->lock);
    pthread_mutex_unlock(&philo->fork_two->lock);
    philo->meal_count++;
}

void    philo_sleep(t_philo *philo)
{
    print_status(philo, 3);
    sleep_for(philo->param->time_sleep, philo);
}

void    philo_think(t_philo *philo)
{
    print_status(philo, 4);
}
