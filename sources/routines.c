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
static void	thinking(t_phil	*philosopher)
{	
	status(philosopher, THNK);
	pthread_mutex_lock(philosopher->lfork);
	status(philosopher, FORK);
	pthread_mutex_lock(philosopher->rfork);	
	status(philosopher, FORK);
}

//This is an accurate description of an hungover philosopher's routine. At 
//first, they try to grab the fork on their left. If it fails, they pretend life
// and start regretting all this liquor ingested last night. Once they grab the
//fork, their focus shifts to grabbing the second fork.
//After ingesting all thos spaghettis, they feel sleepy hence take a nap. 
void    *routine(void *arg)
{
    t_phil	*philosopher;

    philosopher = (t_phil *)arg;
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

		thinking(philosopher);
		set_value(&philosopher->table->monitoring, (void *)&philosopher->stats[LMEAL], (void *)get_timestamp());
		eating(philosopher);
		philosopher->stats[EATEN]++;
		sleeping(philosopher);
    }
    return (philosopher);
}

//Set STS to -1	->	Simulation should end
