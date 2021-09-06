/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoanne <cjoanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 04:56:46 by cjoanne           #+#    #+#             */
/*   Updated: 2021/09/06 21:14:08 by cjoanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_time(uint64_t start)
{
	struct timeval	tm;

	gettimeofday(&tm, NULL);
	return (tm.tv_sec * 1000 + (tm.tv_usec / 1000) - start);
}

void	ft_usleep(uint64_t n)
{
	uint64_t	cur_time;

	cur_time = get_time(0);
	usleep((n - 15) * 1000);
	while (1)
	{
		usleep(50);
		if (get_time(0) >= cur_time + n)
			break ;
	}
}

int	ft_error(char *str)
{
	printf("%s", str);
	return (ERROR);
}

void	philo_free(t_philo *philo, pthread_t *philo_thread, t_data *data)
{
	usleep(420000);
	if (philo != NULL)
		free(philo);
	if (philo_thread != NULL)
		free(philo_thread);
	if (data->mtxs != NULL)
		free(data->mtxs);
}
