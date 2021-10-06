/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nephilister <nephilister@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 04:56:46 by cjoanne           #+#    #+#             */
/*   Updated: 2021/10/06 05:48:02 by nephilister      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

uint64_t	get_time(uint64_t start)
{
	struct timeval	tm;

	gettimeofday(&tm, NULL);
	return (tm.tv_sec * 1000 + (tm.tv_usec / 1000) - start);
}

void	ft_usleep(uint64_t n)
{
	struct timeval	i;
	struct timeval	j;

	n *= 1000;
	gettimeofday(&i, NULL);
	while (42)
	{
		gettimeofday(&j, NULL);
		if (((j.tv_usec - i.tv_usec + (j.tv_sec - i.tv_sec) * 1000000)) > n)
			break ;
		usleep(100);
	}
}

int	ft_error(char *str)
{
	printf("%s", str);
	exit(1);
}
