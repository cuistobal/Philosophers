#ifndef STRUCTURES_BONUS_H
# define STRUCTURES_BONUS_H

typedef struct philo
{
	p_thread	thread;
	pid_t	pid;
	t_tabl	*table;
	long	stats[STATS];
}	t_phil;

typedef struct table
{
	p_thread	thread;
	pid_t	pid;
	sem_t	forks;
	t_phil	*philos;
	long	params[PARAMS];
}	t_tabl;

#endif
