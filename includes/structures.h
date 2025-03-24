#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct	fork
{
	pthread_mutex_t
}	t_fork;

typedef struct	philo
{
	int			stats[STATS];
    pthread_t   thread;
}	t_phil;

typedef struct	table
{
	int				params[PARAMS];
	pthread_mutex_t	*fork;
	struct	philo	*philo;
}	t_tabl;

#endif
