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
	// creat_threads(&data);
	return (0);
}

// int	creat_threads(t data)