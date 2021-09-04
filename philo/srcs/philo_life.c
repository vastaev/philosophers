#include "philo.h"

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