#include "philo.h"

int	parsing_args(t_data *data, int argc, char *argv[])
{
	data->number = ft_atoi_long(argv[1]);
	data->toDie = ft_atoi_long(argv[2]);
	data->toEat = ft_atoi_long(argv[3]);
	data->toSleep = ft_atoi_long(argv[4]);
	if (argc == 6)
	{
		data->isLimitedMeals = true;
		data->mealsCounter = ft_atoi_long(argv[5]);
	}
	if (data->number < 1 || data->number > 200)
		return (ft_error("Error: bad philos number\n"));
	if (data->toDie < 25)
		return (ft_error("Error: bad time to die\n"));
	if (data->toEat < 25)
		return (ft_error("Error: bad time to eat\n"));
	if (data->toSleep < 25)
		return (ft_error("Error: bad time to sleep\n"));
	if (data->isLimitedMeals == true && data->mealsCounter < 1)
		return (ft_error("Error: bad meals counter\n"));
	return (0);
}

int	init_data(t_data *data)
{
	u_int32_t	i;

	data->time = get_time(0);
	data->ateNum = 0;
	data->isAllAlive = true;
	data->startNum = 0;
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
