#include "philosophers.h"

suseconds_t	get_timestamp(void)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return (current.tv_sec * MSEC + (current.tv_usec / MSEC));
}
