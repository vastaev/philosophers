#include "philo.h"

static void	take_forks(t_philo *philo);
static void	eating(t_philo *philo);
static void	clear_messaging(t_philo *philo, char *msg);

void	*philo_life(void *philosopher)
{
	t_philo *philo;

	philo = (t_philo *)philosopher;
	while (21)
	{
		take_forks(philo);
		eating(philo);
		clear_messaging(philo, SLEEPING);
		ft_usleep(philo->data->toSleep * 1000);
		clear_messaging(philo, THINKING);
	}
}

static void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mtxs[philo->leftForkInd]);
	clear_messaging(philo, LFORK);
	pthread_mutex_lock(&philo->data->mtxs[philo->rightForkInd]);
	clear_messaging(philo, RFORK);
}

static void	eating(t_philo *philo)
{
	philo->lastMealTime = get_time(0);
	clear_messaging(philo, EATING);
	ft_usleep(philo->data->toEat * 1000);
	if (philo->data->isLimitedMeals == true)
	{
		philo->mealsLeft--;
		if (philo->mealsLeft == 0)
			philo->data->ateNum++;
	}
	pthread_mutex_unlock(&philo->data->mtxs[philo->leftForkInd]);
	pthread_mutex_unlock(&philo->data->mtxs[philo->rightForkInd]);
}

static void	clear_messaging(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->messenger);
	if (philo->data->isAllAlive == true)
		printf("%llu %u %s\n", get_time(philo->data->time), philo->pos, msg);
	pthread_mutex_unlock(&philo->data->messenger);
}
