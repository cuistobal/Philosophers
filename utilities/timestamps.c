#include "philosophers.h"

suseconds_t	get_timestamp(void)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return (current.tv_sec * 1000 + (current.tv_usec / 1000));
}
