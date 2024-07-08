/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 22:05:27 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/07/07 22:05:29 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/include.h"

void	sleep_for(long ms, t_philo *philo)
{
	long	start;
	long	elapsed;
	long	rem;

	start = timestamp_in('u');
	ms *= 1000;
	(void)philo;
	while (timestamp_in('u') - start < ms)
	{
		usleep(100);
		elapsed = timestamp_in('u') - start;
		rem = ms - elapsed;
		if (rem > 1000)
			usleep(rem / 2);
		else
			while (timestamp_in('u') - start < ms)
				;
	}
}

long	timestamp_in(char c)
{
	struct timeval	tv;
	long			ret;

	gettimeofday(&tv, NULL);
	if (c == 'u')
		ret = tv.tv_usec + tv.tv_sec * 1000000;
	else
		ret = tv.tv_usec / 1000 + tv.tv_sec * 1000;
	return (ret);
}
