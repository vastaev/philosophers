/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nephilister <nephilister@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 04:56:40 by cjoanne           #+#    #+#             */
/*   Updated: 2021/10/06 01:37:23 by nephilister      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	parsing_args(t_data *data, int argc, char *argv[])
{
	data->number = ft_atoi_long(argv[1]);
	data->toDie = ft_atoi_long(argv[2]);
	data->toEat = ft_atoi_long(argv[3]);
	data->toSleep = ft_atoi_long(argv[4]);
	if (argc == 6)
	{
		data->isLimitedMeals = true;
		data->mealsCounter = ft_atoi_long(argv[5]);
	}
	if (data->number < 1 || data->number > 200)
		return (ft_error("Error: bad philos number\n"));
	if (data->toDie < 25)
		return (ft_error("Error: bad time to die\n"));
	if (data->toEat < 25)
		return (ft_error("Error: bad time to eat\n"));
	if (data->toSleep < 25)
		return (ft_error("Error: bad time to sleep\n"));
	if (data->isLimitedMeals == true && data->mealsCounter < 1)
		return (ft_error("Error: bad meals counter\n"));
	return (0);
}

int	init_data(t_data *data)
{
	u_int32_t	i;

	data->time = get_time(0);
	data->ateNum = 0;
	data->pids = malloc(sizeof(pid_t) * data->number);
	sem_unlink("forks");
	sem_unlink("both_forks");
	data->forks = sem_open("forks", O_CREAT, S_IRWXU, data->number);
	data->both_forks = sem_open("both_forks", O_CREAT, S_IRWXU, data->number);
	data->messenger = sem_open("messenger", O_CREAT, S_IRWXU, 1);
	return (0);
}

