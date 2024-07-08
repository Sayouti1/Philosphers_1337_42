/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 22:05:20 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/07/07 22:05:22 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/include.h"

// void	print_status(t_philo *philo, int status)
// {
// 	long	time;

// 	pthread_mutex_lock(&philo->param->print_lock);
// 	time = (timestamp_in('m') - get_lvalue(&philo->param->lock,
// 				&philo->param->start_time));
// 	if (status == 0)
// 	{
// 		set_value(&philo->param->lock, &philo->param->end, 1);
// 		if (get_value(&philo->param->lock, &philo->param->exit) == 0)
// 			printf("%ld %d died\n", time, philo->id);
// 		set_value(&philo->param->lock, &philo->param->exit, 1);
// 	}
// 	else if (status == 1 && !get_value(&philo->param->lock, &philo->param->end))
// 		printf("%ld %d has taken a fork\n", time, philo->id);
// 	else if (status == 2 && !get_value(&philo->param->lock, &philo->param->end))
// 		printf("%ld %d is eating\n", time, philo->id);
// 	else if (status == 3 && !get_value(&philo->param->lock, &philo->param->end))
// 		printf("%ld %d is sleeping\n", time, philo->id);
// 	else if (status == 4 && !get_value(&philo->param->lock, &philo->param->end))
// 		printf("%ld %d is thinking\n", time, philo->id);
// 	pthread_mutex_unlock(&philo->param->print_lock);
// }

void	print_status(t_philo *philo, char *str)
{
	long	time;

	pthread_mutex_lock(&philo->param->print_lock);
	time = (timestamp_in('m') - get_lvalue(&philo->param->lock, &philo->param->start_time));
	if (!get_value(&philo->param->lock, &philo->param->end))
		printf("%ld %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->param->print_lock);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_one->lock);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->fork_two->lock);
	print_status(philo, "has taken a fork");

	print_status(philo, "is eating");

	set_lvalue(&philo->lock, &philo->last_eat, timestamp_in('m'));

	sleep_for(philo->param->time_eat, philo);
	
	pthread_mutex_unlock(&philo->fork_one->lock);
	pthread_mutex_unlock(&philo->fork_two->lock);

	pthread_mutex_lock(&philo->lock);
	philo->meal_count++;
	pthread_mutex_unlock(&philo->lock);
	

	if (philo->param->limit_meals != -1
			&& philo->meal_count >= philo->param->limit_meals)
		set_value(&philo->lock, &philo->is_full, 1);
}

void	philo_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping");
	sleep_for(philo->param->time_sleep, philo);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (get_value(&philo->param->lock, &philo->param->all_ready) == 0)
	;
	set_lvalue(&philo->lock, &philo->last_eat,
		get_lvalue(&philo->param->lock, &philo->param->start_time));
	
	if (philo->id % 2 == 0)
		usleep(100);
	while (get_value(&philo->param->lock, &philo->param->end) == 0)
	{
		philo_eat(philo);
		philo_sleep(philo);
		print_status(philo, "is thinking");
		if (philo->param->limit_meals != -1 && philo->is_full)
			break ;
	}
	return (NULL);
}