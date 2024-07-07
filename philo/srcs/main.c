/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 09:17:39 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/07/07 22:05:07 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/include.h"

int	main(int ac, char **av)
{
	t_param	param;

	if (ac != 5 && ac != 6)
		return (1);
	param.all_ready = 0;
	param.end = 0;
	param.exit = 0;
	if (init_param(ac, av, &param))
		return (printf("init_param\n"), 1);
	init_philos(&param);
	free(param.fork);
	free(param.philo);
	return (0);
}
