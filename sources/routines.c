#include "philosophers.h"

// *rompiche intensifies*
static void	sleeping(t_phil *philosopher)
{
	status(philosopher, SLEP);
	usleep(philosopher->table->params[SLP] * MSEC);
}

// *scronch scronch scronch*
static void	eating(t_phil *philosopher)
{
	status(philosopher, EATS);
	usleep(philosopher->table->params[EAT] * MSEC);
	pthread_mutex_unlock(philosopher->lfork);
	pthread_mutex_unlock(philosopher->rfork);
}

//The philos are right handed if an even number sits around the table. They 
//become left handed otherwise.
static void	thinking(t_phil	*philosopher, bool even)
{	
	status(philosopher, THNK);
	if (even)
	{
		pthread_mutex_lock(philosopher->lfork);
		status(philosopher, FORK);
		pthread_mutex_lock(philosopher->rfork);	
		status(philosopher, FORK);
	}
	else
	{
		pthread_mutex_lock(philosopher->rfork);	
		status(philosopher, FORK);
		pthread_mutex_lock(philosopher->lfork);
		status(philosopher, FORK);
	}
}

static void	set_even(t_phil *philosopher, bool *even)
{
	long			count;

	count = (long)access_value(&philosopher->table->monitoring, (void *)philosopher->table->params[CNT]);
	if (count & 1)
		*even = true;
	else
		*even = false;
}

//This is an accurate description of an hungover philosopher's routine. At 
//first, they try to grab the fork on their left. If it fails, they pretend life
// and start regretting all this liquor ingested last night. Once they grab the
//fork, their focus shifts to grabbing the second fork.
//After ingesting all thos spaghettis, they feel sleepy hence take a nap. 
void    *routine(void *arg)
{
	bool	even;
    t_phil	*philosopher;

    philosopher = (t_phil *)arg;
    set_even(philosopher, &even);
	while (true)
    {

		pthread_mutex_lock(&philosopher->table->monitoring);

		//Acceder a la variable de monitoring
		//Verifier que simulation peut continuer
		//Rendre la variable de monitoring

		//if (the_show_must_go_on(philosopher))
		if (you_are_dead(philosopher))	
		{
			pthread_mutex_unlock(&philosopher->table->monitoring);
			status(philosopher, DIED);	
			break ;
		}

		pthread_mutex_unlock(&philosopher->table->monitoring);

		//Pense -> Mange -> Dort	

		thinking(philosopher, even);
		philosopher->stats[LMEAL] = get_timestamp();
		eating(philosopher);
		philosopher->stats[EATEN]++;
		sleeping(philosopher);
    }
    return (philosopher);
}

//Set STS to -1	->	Simulation should end
