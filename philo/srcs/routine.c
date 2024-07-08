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
	if (philo->id == philo->param->num_philos)
		usleep(2000);
	pthread_mutex_lock(&philo->fork_one->lock);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->fork_two->lock);
	print_status(philo, "has taken a fork");

	print_status(philo, "\033[1;32mis eating\033[0m");

	set_lvalue(&philo->lock, &philo->last_eat, timestamp_in('m'));

	sleep_for(philo->param->time_eat, philo);
	
	pthread_mutex_unlock(&philo->fork_two->lock);
	pthread_mutex_unlock(&philo->fork_one->lock);

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
	
	if (philo->param->num_philos % 2 && philo->id % 2 == 0)
		usleep(100);
	while (get_value(&philo->param->lock, &philo->param->end) == 0)
	{
		philo_eat(philo);
		philo_sleep(philo);
		print_status(philo, "is thinking");
		if (philo->param->num_philos % 2)
			sleep_for(60 , philo);
		if (philo->param->limit_meals != -1 && philo->is_full)
			break ;
	}
	return (NULL);
}