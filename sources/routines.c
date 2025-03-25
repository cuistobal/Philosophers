#include "philosophers.h"
/*
static bool	sleeping(t_phil *philosopher)
{

}

//
static bool	eating(t_phil *philosopher)
{
	
}

//
static bool	thinking(t_phil	*philosopher)
{
				
}*/


//static inline bool delcared in the .h instead
inline static bool	you_are_dead(t_phil	*philo)
{
	return ((philo->stats[LMEAL] - get_timestamp()) > 0);
}

//This is an accurate description of an hungover philosopher's routine. At 
//first, they try to grab the fork on their left. If it fails, they pretend life
// and start regretting all this liquor ingested last night. Once they grab the
//fork, their focus shifts to grabbing the second fork.
//After ingesting all thos spaghettis, they feel sleepy hence take a nap. 
void    *routine(void *arg)
{
	bool		status;
    t_phil		*philosopher;

	status = true;
    philosopher = (t_phil *)arg;
    while (status)
    {
		printf("%ld %ld %s\n",get_timestamp, philosopher->stats[POSTN], THNK);

		if (!you_are_dead(philosopher))
			break ;
        //tries to get the forks
        pthread_mutex_lock(philosopher->lfork); 
		printf("%ld %ld %s\n", time, philosopher->stats[POSTN], FORK);
		
		if (!you_are_dead(philosopher))
		{
        
			pthread_mutex_unlock(philosopher->lfork);
			break ;
		}
        pthread_mutex_lock(philosopher->rfork);
        printf("%ld %ld %s\n", time, philosopher->stats[POSTN], FORK);

		if (!you_are_dead(philosopher))
		{
        	pthread_mutex_unlock(philosopher->lfork);
        	pthread_mutex_unlock(philosopher->rfork);
			break ;
		}

        printf("%ld %ld %s\n", time, philosopher->stats[POSTN], EATS);
        usleep(philosopher->params[EAT]);
	
        //forks releasing
        pthread_mutex_unlock(philosopher->lfork);
        pthread_mutex_unlock(philosopher->rfork);

		get_timestamp(&time);
		philosopher->stats[LMEAL] = time;
        
		printf("%ld %ld %s\n", time, philosopher->stats[POSTN], SLEP);
        
        usleep(philosopher->params[SLP]);
	
    }
	pthread_detach(philosopher->thread);
    return NULL;
}
