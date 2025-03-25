#include "philosophers.h"

static bool	sleeping(t_phil *philosopher)
{
	status(philosopher, SLEP);
	usleep(philosopher->table->params[SLP] * MSEC);
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
	printf("%d	->	%ld\n", philo->stats[POSTN] ,philo->stats[LMEAL] - get_timestamp());
	
	return ((philo->stats[LMEAL] - get_timestamp()) > 0);
}

/*
inline static bool	diner_is_over(t_phil *philosopher)
{
	if  	
		return true;
	return false;
}*/

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

		//Acceder a la variable de monitoring
		//Verifier que simulation peut continuer
		//Rendre la variable de monitoring

		if (you_are_dead(philosopher))
		{
			pthread_mutex_unlock(&philosopher->table->monitoring);

			break ;
		}
		pthread_mutex_unlock(&philosopher->table->monitoring);

		//Pense -> Mange -> Dort	

		thinking(philosopher);
		philosopher->stats[LMEAL] = get_timestamp();
		eating(philosopher);
		sleeping(philosopher);

    }
    return NULL;
}
