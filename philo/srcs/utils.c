/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 22:05:34 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/07/07 22:05:37 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/include.h"

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isspace(char c)
{
	return ((c >= 7 && c <= 13) || c == 32);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		++i;
	return (i);
}

long	ft_atol(char *str)
{
	long	num;
	int		i;

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

int	philo_died(t_philo *philo)
{
	long time_passed;

	if (get_value(&philo->lock, &philo->is_full) == 1)
		return (0);
	time_passed = timestamp_in('m') - get_lvalue(&philo->lock, &philo->last_eat);
	if (time_passed > philo->param->time_die)
	{
		// set_value(&philo->param->lock, &philo->param->end, 1);
		print_status(0, philo, "\033[1;31mis died\033[0m", 0);
		return (1);
	}
	return (0);
}
