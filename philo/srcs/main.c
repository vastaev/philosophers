/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoanne <cjoanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 04:56:36 by cjoanne           #+#    #+#             */
/*   Updated: 2021/09/05 05:43:12 by cjoanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	creat_thrds(t_philo *philo, pthread_t *philo_thread, t_data *data);
static int	create_philo(t_philo *philo, pthread_t *philo_thread, t_data *data);
static void	*waiter_actions(void *philosopher);

int	main(int argc, char *argv[])
{
	t_data		data;
	t_philo		*philo;
	pthread_t	*philo_thread;

	if (validation_of_args(argc, argv) == ERROR)
		return (ERROR);
	if (parsing_args(&data, argc, argv) == ERROR)
		return (ERROR);
	if (init_data(&data) == ERROR)
		return (ERROR);
	if (init_philo(&philo, &philo_thread, &data) == ERROR)
	{
		philo_free(philo, philo_thread, &data);
		return (ERROR);
	}
	if (creat_thrds(philo, philo_thread, &data) == ERROR)
	{
		philo_free(philo, philo_thread, &data);
		return (ERROR);
	}
	philo_free(philo, philo_thread, &data);
	return (0);
}

static int	creat_thrds(t_philo *philo, pthread_t *philo_thread, t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->number)
	{
		philo[i].rightForkInd = i;
		if (i == 0)
			philo[i].leftForkInd = data->number - 1;
		else
			philo[i].leftForkInd = i - 1;
		philo[i].pos = i + 1;
		philo[i].mealsLeft = data->mealsCounter;
		philo[i].data = data;
		i++;
	}
	if (create_philo(philo, philo_thread, data) == ERROR)
		return (ERROR);
	data->startNum++;
	if (create_philo(philo, philo_thread, data) == ERROR)
		return (ERROR);
	if (pthread_create(&data->waiter_thread, NULL, &waiter_actions, philo))
		return (ERROR);
	pthread_join(data->waiter_thread, NULL);
	return (0);
}

static int	create_philo(t_philo *philo, pthread_t *philo_thread, t_data *data)
{
	uint32_t	i;

	i = data->startNum;
	while (i < data->number)
	{
		philo[i].lastMealTime = get_time(0);
		if (pthread_create(&philo_thread[i], NULL, &philo_life, &philo[i]))
			return (ft_error("Error: creating philo thread fail"));
		pthread_detach(philo_thread[i]);
		i = i + 2;
	}
	usleep(100);
	return (0);
}

static void	*waiter_actions(void *philosopher)
{
	t_philo		*philo;
	uint32_t	i;

	i = 0;
	philo = (t_philo *)philosopher;
	while (21)
	{
		if (get_time(philo[i].lastMealTime) > philo[i].data->toDie)
		{
			philo->data->isAllAlive = false;
			pthread_mutex_lock(&philo->data->messenger);
			printf("%llu %u is dead\n", get_time(philo[i].data->time),
				philo[i].pos);
			return (NULL);
		}
		else if (philo->data->number == philo->data->ateNum)
		{
			pthread_mutex_lock(&philo->data->messenger);
			return (NULL);
		}
		i++;
		if (i == philo->data->number)
			i = 0;
		usleep(10);
	}
}
