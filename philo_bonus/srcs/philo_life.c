/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nephilister <nephilister@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 04:56:44 by cjoanne           #+#    #+#             */
/*   Updated: 2021/10/06 01:36:54 by nephilister      ###   ########.fr       */
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
		if (get_time(philo->lastMealTime) > philo->data->toDie)
		{
			sem_wait(philo->data->messenger);
			printf("%llu %u is dead\n", 
					get_time(philo->lastMealTime), philo->pos);
			exit(1);
		}
		if (philo->data->isLimitedMeals && philo->mealsLeft == 0)
			exit(0);
	}
}

void	*philo_life(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	pthread_detach(philo->thread);
	philo->lastMealTime = get_time(0);
	while (21)
	{
		take_forks(philo);
		eating(philo);
		clear_messaging(philo, SLEEPING);
		while (get_time(philo->lastMealTime) < philo->data->toEat 
				+ philo->data->toSleep)
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
	if (get_time(philo->lastMealTime) < philo->data->toDie)
	{
		philo->lastMealTime = get_time(0);
		clear_messaging(philo, EATING);
	}
	else
		usleep(philo->data->toDie * 1000);
	while (get_time(philo->lastMealTime) < philo->data->toEat)
		usleep(300);
	if (philo->data->isLimitedMeals == true)
		philo->mealsLeft--;
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

static void	clear_messaging(t_philo *philo, char *msg)
{
	sem_wait(philo->data->messenger);
	printf("%llu %u %s\n", get_time(philo->data->time + 1), philo->pos, msg);
	sem_post(philo->data->messenger);
}
