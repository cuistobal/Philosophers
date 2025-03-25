#include "philosophers.h"

void	get_timestamp(u_int64_t *time)
{
	struct timeval	current;

	if (gettimeofday(&current, NULL))
		//error message -> failed tor etrieve timesta,p;
		return ;
	*time =	current.tv_sec * (u_int64_t)1000 + (current.tv_usec / 1000);
}
