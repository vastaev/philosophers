#include "philo.h"

int main(int argc, char *argv[])
{
	t_data		data;
	t_philo		*philo;
	pthread_t	*philo_thread;

	if (validation_of_args(argc, argv) == ERROR)
		return (ERROR);
	if (parsing_args(&data, argc, argv) == ERROR)
		return (ERROR);
	init_data(&data);
	init_philo(&philo, &philo_thread, &data);
	create_threads(philo, philo_thread, &data);
	return (0);
}

int	create_threads(t_philo *philo, pthread_t *philo_thread, t_data *data)
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
		philo[i].mealsCount = data->mealsCounter;
		philo[i].data = data;
		i++;
	}
	if (create_philo(philo, data, philo_thread) == ERROR)
		return (ERROR);
	data->startNum++;
	if (create_philo(philo, data, philo_thread) == ERROR)
		return (ERROR);
	if (pthread_create(&data->waiter_thread, NULL, &waiter_actions, philo))
		return (ERROR);
	pthread_join(data->waiter_thread, NULL);
	return (0);
}

int	create_philo(t_philo *philo, pthread_t *philo_thread, t_data *data)
{
	uint32_t	i;

	i = data->startNum;
	while (i < data->number)
	{
		philo->lastMeal = get_time(0);
		if (pthread_create(&philo_thread[i], NULL, &philo_life, &(philo[i])))
			return (ft_error("Error: creating philo thread"));
		pthread_detach(philo_thread[i]);
		i = i + 2;
	}
	usleep(100);
	return (0);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->data.);
}
