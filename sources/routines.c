#include "philosophers.h"


//This is an accurate description of an hungover philosopher's routine. At 
//first, they try to grab the fork on their left. If it fails, they pretend life
// and start regretting all this liquor ingested last night. Once they grab the
//fork, their focus shifts to grabbing the second fork.
//After ingesting all thos spaghettis, they feel sleepy hence take a nap. 
void    *routine(void *arg)
{
	int		time;
    t_phil  *philosopher;

    philosopher = (t_phil *)arg;
    while (1)
    {
		get_timestamp(&time);
        printf("%d %d %s\n", philosopher->stats[] ,philosopher->stats[POSTN], THINK);
        
        //tries to get the forks
        pthread_mutex_lock(philosopher->lfork);
        printf("%s %d %s\n", PHILO, philosopher->stats[POSTN], LFORK);

        pthread_mutex_lock(philosopher->rfork);
        printf("%s %d %s\n", PHILO, philosopher->stats[POSTN], RFORK);
    
        printf("%s %d %s\n", PHILO, philosopher->stats[POSTN], EATS);
        usleep(philosopher->params[EAT]);
        
        //forks releasing
        pthread_mutex_unlock(philosopher->rfork);
        pthread_mutex_unlock(philosopher->lfork);

        printf("%s %d %s\n", PHILO, philosopher->stats[POSTN], SLEEP);
        
        usleep(philosopher->params[SLP]);
    }
    return NULL;
}
