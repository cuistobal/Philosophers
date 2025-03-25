#include "philosophers.h"

static bool	sleeping(t_phil *philosopher)
{
	status(philosopher, SLEP);
	usleep(philosopher->table->params[SLP]);
	return true;
}

//
static bool	eating(t_phil *philosopher)
{	
	status(philosopher, EATS);
	pthread_mutex_unlock(philosopher->lfork);
	pthread_mutex_unlock(philosopher->rfork);
	return true;
}

//
static bool	thinking(t_phil	*philosopher)
{	
	status(philosopher, THNK);
	pthread_mutex_lock(philosopher->lfork);
	status(philosopher, FORK);
	pthread_mutex_lock(philosopher->rfork);	
	status(philosopher, FORK);
	return true;
}


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
    t_phil		*philosopher;

    philosopher = (t_phil *)arg;
    while (1)
    {
		pthread_mutex_lock(&philosopher->table->monitoring);
//		if ()
//		{
//			pthread_mutex_unlock();
//			break ;
//		}
		pthread_mutex_unlock(&philosopher->table->monitoring);
		//Acceder a la variable de monitoring
		//Verifier que simulation peut continuer
		//Rendre la variable de monitoring

		//Pense -> Mange -> Dort	
		thinking(philosopher);
		eating(philosopher);
		sleeping(philosopher);

		/*
		printf("%ld %d %s\n", (long int)get_timestamp, philosopher->stats[POSTN], THNK);

        //tries to get the forks
        pthread_mutex_lock(philosopher->lfork); 
		printf("%ld %d %s\n", (long int)get_timestamp, philosopher->stats[POSTN], FORK);
		
        pthread_mutex_lock(philosopher->rfork);
        printf("%ld %d %s\n", (long int)get_timestamp, philosopher->stats[POSTN], FORK);

        printf("%ld %d %s\n", (long int)get_timestamp, philosopher->stats[POSTN], EATS);
        usleep(philosopher->params[EAT]);
	
        //forks releasing
        pthread_mutex_unlock(philosopher->lfork);
        pthread_mutex_unlock(philosopher->rfork);
        
		printf("%ld %d %s\n", (long int)get_timestamp, philosopher->stats[POSTN], SLEP);
        
        usleep(philosopher->params[SLP]);
		*/	
    }
    return NULL;
}
