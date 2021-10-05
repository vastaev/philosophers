/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nephilister <nephilister@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 04:56:44 by cjoanne           #+#    #+#             */
/*   Updated: 2021/10/06 01:00:26 by nephilister      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philo *philo);
static void	eating(t_philo *philo);
static void	clear_messaging(t_philo *philo, char *msg);

void	*philo_life(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	while (21)
	{
		take_forks(philo);
		eating(philo);
		clear_messaging(philo, SLEEPING);
		ft_usleep(philo->data->toSleep);
		clear_messaging(philo, THINKING);
	}
}

static void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->mtxs[philo->first_fork]));
	clear_messaging(philo, FORK);
	pthread_mutex_lock(&(philo->data->mtxs[philo->second_fork]));
	clear_messaging(philo, FORK);
}

static void	eating(t_philo *philo)
{
	philo->last_meal_time = get_time(0);
	clear_messaging(philo, EATING);
	ft_usleep(philo->data->toEat);
	if (philo->data->isLimitedMeals == true)
	{
		philo->mealsLeft--;
		if (philo->mealsLeft == 0)
			philo->data->ateNum++;
	}
	pthread_mutex_unlock(&philo->data->mtxs[philo->second_fork]);
	pthread_mutex_unlock(&philo->data->mtxs[philo->first_fork]);
}

static void	clear_messaging(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->messenger);
	if (philo->data->isAllAlive == true)
		printf("%llu %u %s\n", get_time(philo->data->time), philo->pos, msg);
	pthread_mutex_unlock(&philo->data->messenger);
}
