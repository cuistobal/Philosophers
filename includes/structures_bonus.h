#ifndef STRUCTURES_BONUS_H
# define STRUCTURES_BONUS_H

//
typedef struct philo
{
	pid_t	pid;
	t_tabl	*table;
	long	stats[STATS];
}	t_phil;

//
typedef struct table
{
	pid_t		*pids;
	t_phil		*philos;
	sem_t		*semaphors;
	p_thread	monitoring;
	long		params[PARAMS];
}	t_tabl;

#endif
