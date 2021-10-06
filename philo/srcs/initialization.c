/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nephilister <nephilister@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 04:56:40 by cjoanne           #+#    #+#             */
/*   Updated: 2021/10/06 05:55:52 by nephilister      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parsing_args(t_data *data, int argc, char *argv[])
{
	data->number = ft_atoi_long(argv[1]);
	data->to_die = ft_atoi_long(argv[2]);
	data->to_eat = ft_atoi_long(argv[3]);
	data->to_sleep = ft_atoi_long(argv[4]);
	if (argc == 6)
	{
		data->is_limited_meals = true;
		data->meals_counter = ft_atoi_long(argv[5]);
	}
	if (data->number < 1 || data->number > 200)
		return (ft_error("Error: bad philos number\n"));
	if (data->to_die < 25)
		return (ft_error("Error: bad time to die\n"));
	if (data->to_eat < 25)
		return (ft_error("Error: bad time to eat\n"));
	if (data->to_sleep < 25)
		return (ft_error("Error: bad time to sleep\n"));
	if (data->is_limited_meals == true && data->meals_counter < 1)
		return (ft_error("Error: bad meals counter\n"));
	return (0);
}

int	init_data(t_data *data)
{
	u_int32_t	i;

	data->time = get_time(0);
	data->ate_num = 0;
	data->is_all_alive = true;
	data->start_num = 0;
	data->mtxs = malloc(sizeof(pthread_mutex_t) * data->number);
	if (!data->mtxs)
		return (ERROR);
	i = 0;
	while (i < data->number)
	{
		if (pthread_mutex_init(&data->mtxs[i], NULL))
			return (ft_error("Error: malloc mutexes fail\n"));
		i++;
	}
	return (0);
}

int	init_philo(t_philo **philo, pthread_t **philo_thread, t_data *data)
{
	*philo = malloc(sizeof(t_philo) * data->number);
	if (!*philo)
		return (ft_error("Error: malloc philos fail\n"));
	*philo_thread = malloc(sizeof(pthread_t) * data->number);
	if (!*philo_thread)
		return (ft_error("Error: malloc philo threads fail\n"));
	if (pthread_mutex_init(&data->messenger, NULL) != 0)
		return (ft_error("Error: messenger init fail\n"));
	return (0);
}
