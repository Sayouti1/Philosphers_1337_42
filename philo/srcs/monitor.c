/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 22:05:12 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/07/07 22:05:15 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/include.h"

void	*ft_monitor(void *arg)
{
	t_param	*param;
	int		i;
	int		j;

	param = (t_param *)arg;
	while (get_value(&param->lock, &param->all_ready) == 0)
		;
	sleep_for(get_lvalue(&param->lock, &param->time_die), NULL);
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
