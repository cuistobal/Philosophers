#include "philosophers.h"

//
void	set_value(pthread_mutex_t *mutex, void **value, void *new)
{
	pthread_mutex_lock(mutex);
	*value = new;
	pthread_mutex_unlock(mutex);
}

//This function allows us to access value thread safely
void	*access_value(pthread_mutex_t *mutex, void *value)
{
	void	*accessed;

	pthread_mutex_lock(mutex);
	accessed = value;
	pthread_mutex_unlock(mutex);
	return (accessed);
}

//
void	status(t_phil *philo, char *status)
{
//	long	time;

//	time = (long)access_value(&philo->table->monitoring, (void *)philo->table->params[STS]);
//	printf("%ld %ld %s", get_timestamp() - time, philo->stats[POSTN], status);
	printf("%ld %ld %s", get_timestamp(), philo->stats[POSTN], status);
}

//
long	get_timestamp(void)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return (current.tv_usec);
}
