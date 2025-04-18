#ifndef STRUCTURES_BONUS_H
# define STRUCTURES_BONUS_H

//
typedef struct phil
{
	pid_t			*pid;
	sem_t			clock;
	struct table	*table;
	long			stats[STATS];
}	t_phil;

//
typedef struct table
{
	pid_t		*pids;
	struct phil	*philo;
	sem_t		*semaphors;
	long		params[PARAMS];
}	t_tabl;

#endif
