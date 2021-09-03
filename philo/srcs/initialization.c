#include "philo.h"

int	parsing_args(t_data *data, int argc, char *argv[])
{
	data->number = ft_atoi_long(argv[1]);
	data->toDie = ft_atoi_long(argv[2]);
	data->toEat = ft_atoi_long(argv[3]);
	data->toSleep = ft_atoi_long(argv[4]);
	if (argc == 6)
	{
		data->isLimitedMeals = argc == 6;
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

int	initialize_data(t_data *data)
{
	u_int32_t	i;

	data->philos = malloc(sizeof(*data->philos) * data->number);
	if (!data->philos)
		return (ft_error("Error: malloc philos\n"));
	data->mtxs = malloc(sizeof(*data->mtxs) * data->number);
	if (!data->mtxs)
		return (ERROR);
	i = 0;
	while (i < data->number)
		if (pthread_mutex_init(&data->mtxs[i++], NULL))
			return (ft_error("Error: malloc mutexes\n"));
	return (0);
}

void	initialize_philos(t_data *data)
{
	u_int32_t	i;

	i = 0;
	while (i < data->number)
	{
		data->philos[i].data = data;
		data->philos[i].pos = i + 1;
		data->philos[i].mealsCount = 0;
		if (i == 0)
			data->philos[i].lFork = &data->mtxs[data->number - 1];
		else
			data->philos[i].lFork = &data->mtxs[i - 1];
		data->philos[i].rFork = &data->mtxs[i];
		i++;
	}
}
