#include "philosophers.h"

//This function allows us to access value thread safely
void	*access_value(pthread_mutex_t *mutex, void *value)
{
	void	*accessed;

	pthread_mutex_lock(mutex);
	accessed = value;	
	pthread_mutex_unlock(mutex);
	return (accessed);
}
