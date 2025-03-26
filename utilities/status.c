#include "philosophers.h"

void	status(t_phil *philo, char *status)
{
	printf("%ld %d %s", (long int)(get_timestamp - philo->table->start_time), philo->stats[POSTN], status);
}
