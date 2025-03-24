#include "philosophers.h"

void	eating(t_tabl **table)
{
	if (*table)
	{
	    pthread_mutex_lock();

        wait();

	    pthread_mutex_unlock();
	}
}

void	sleeping()
{

}

void	thinking()
{

}

void    routine(t_tabl **table)
{
    if ()
}
