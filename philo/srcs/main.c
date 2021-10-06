/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nephilister <nephilister@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 04:56:36 by cjoanne           #+#    #+#             */
/*   Updated: 2021/10/06 05:56:44 by nephilister      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	creat_thrds(t_philo *philo, pthread_t *philo_thread, t_data *data);
static int	create_philo(t_philo *philo, pthread_t *philo_thread, t_data *data);
static void	*waiter_actions(void *philosopher);
static int	data_to_phil(t_philo *philo, pthread_t *philo_thread, t_data *data);

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
	data_to_phil(philo, philo_thread, &data);
	if (creat_thrds(philo, philo_thread, &data) == ERROR)
	{
		philo_free(philo, philo_thread, &data);
		return (ERROR);
	}
	philo_free(philo, philo_thread, &data);
	return (0);
}

static int	data_to_phil(t_philo *philo, pthread_t *philo_thread, t_data *data)
{
	uint32_t	i;

	i = 0;
	while (i < data->number)
	{
		philo[i].right_fork = i;
		philo[i].left_fork = (i + 1) % data->number;
		philo[i].first_fork = ft_m(philo[i].right_fork, philo[i].left_fork);
		if (philo[i].first_fork == philo[i].left_fork)
			philo[i].second_fork = philo[i].right_fork;
		else
			philo[i].second_fork = philo[i].left_fork;
		philo[i].pos = i + 1;
		philo[i].data = data;
		if (philo[i].data->is_limited_meals == true)
			philo[i].meals_left = data->meals_counter;
		i++;
	}
	return (0);
}

static int	creat_thrds(t_philo *philo, pthread_t *philo_thread, t_data *data)
{
	if (create_philo(philo, philo_thread, data) == ERROR)
		return (ERROR);
	data->start_num++;
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

	i = data->start_num;
	while (i < data->number)
	{
		philo[i].last_meal_time = get_time(0);
		pthread_create(&philo_thread[i], NULL, &philo_life, &philo[i]);
		pthread_detach(philo_thread[i]);
		i += 2;
		usleep(100);
	}
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
		if (get_time(philo[i].last_meal_time) > philo[i].data->to_die)
		{
			philo->data->is_all_alive = false;
			pthread_mutex_lock(&philo->data->messenger);
			printf("%llu %u is dead\n", get_time(philo[i].data->time),
				philo[i].pos);
			return (NULL);
		}
		else if (philo->data->number == philo->data->ate_num)
		{
			pthread_mutex_lock(&philo->data->messenger);
			return (NULL);
		}
		i++;
		if (i == philo->data->number)
			i = 0;
		usleep(1000);
	}
}
