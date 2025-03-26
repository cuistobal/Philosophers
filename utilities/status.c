#include "philosophers.h"

void	status(t_phil *philo, char *status)
{
	suseconds_t	time;

	time = get_timestamp - philo->table->start_time;
	printf("%ld %d %s", (long int)time, philo->stats[POSTN], status);
}
