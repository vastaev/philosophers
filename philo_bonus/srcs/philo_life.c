/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nephilister <nephilister@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 04:56:44 by cjoanne           #+#    #+#             */
/*   Updated: 2021/10/06 05:48:31 by nephilister      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	take_forks(t_philo *philo);
static void	eating(t_philo *philo);
static void	clear_messaging(t_philo *philo, char *msg);

void	child_philos(t_philo *philo)
{
	if (pthread_create(&philo->thread, NULL, philo_life, philo) == -1)
		ft_error("Error: creating philo thread fail");
	while (true)
	{
		usleep(3000);
		if (get_time(philo->last_meal_time) > philo->data->to_die)
		{
			sem_wait(philo->data->messenger);
			printf("%llu %u is dead\n",
				get_time(philo->last_meal_time), philo->pos);
			exit(1);
		}
		if (philo->data->is_limited_meals && philo->meals_left == 0)
			exit(0);
	}
}

void	*philo_life(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	pthread_detach(philo->thread);
	philo->last_meal_time = get_time(0);
	while (21)
	{
		take_forks(philo);
		eating(philo);
		clear_messaging(philo, SLEEPING);
		while (get_time(philo->last_meal_time) < philo->data->to_eat
			+ philo->data->to_sleep)
			usleep(300);
		clear_messaging(philo, THINKING);
	}
}

static void	take_forks(t_philo *philo)
{
	sem_wait(philo->data->both_forks);
	sem_wait(philo->data->forks);
	clear_messaging(philo, FORK);
	sem_wait(philo->data->forks);
	sem_post(philo->data->both_forks);
	clear_messaging(philo, FORK);
}

static void	eating(t_philo *philo)
{
	if (get_time(philo->last_meal_time) < philo->data->to_die)
	{
		philo->last_meal_time = get_time(0);
		clear_messaging(philo, EATING);
	}
	else
		usleep(philo->data->to_die * 1000);
	while (get_time(philo->last_meal_time) < philo->data->to_eat)
		usleep(300);
	if (philo->data->is_limited_meals == true)
		philo->meals_left--;
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

static void	clear_messaging(t_philo *philo, char *msg)
{
	sem_wait(philo->data->messenger);
	printf("%llu %u %s\n", get_time(philo->data->time + 1), philo->pos, msg);
	sem_post(philo->data->messenger);
}
