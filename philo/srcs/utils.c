#include "philo.h"

uint64_t	get_time(void)
{
	struct timeval tm;

	gettimeofday(&tm, NULL);
	return (tm.tv_sec * 1000 + tm.tv_usec / 1000);
}

int	ft_error(char *str)
{
	printf("%s", str);
	return (ERROR);
}