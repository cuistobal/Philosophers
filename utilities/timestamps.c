#include "philosophers.h"

bool	get_timestamp(int *time)
{
	struct timeval	current;

	if (gettimeofday(&current, NULL))
	{
		*time = current.tv_usec;
		return (true);
	}
	return (false);	
}
