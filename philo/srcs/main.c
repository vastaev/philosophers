#include "philo.h"

int main(int argc, char *argv[])
{
	t_data	data;

	if (validation_of_args(argc, argv) == ERROR)
		return (ERROR);
	if (parsing_args(&data, argc, argv) == ERROR)
		return (ERROR);
	initialize_data(&data);
	initialize_philos(&data);
	creat_threads(&data);
	return (0);
}

int	creat_threads(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->number)
	{
		if (pthread_create(data->philos[i].thread, NULL, 
				philo_life, (void *)(data->philos + i)))
				return (ERROR);
		i += 2;
		if (i >= data->number && !(i % 2))
			i = 1;
		usleep(10);
	}
	return (0);
}

void	*philo_life(void *philosopher)
{
	t_philo *philo;
	t_data	*data;

	philo = (t_philo *)philosopher;
	data = (t_data *)philo->data;
	philo->birth = get_time(0);
	philo->lastMeal = philo->birth;
	while (21)
	{
		take_forks(philo);
	}
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->data.);
