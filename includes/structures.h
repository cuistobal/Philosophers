#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct	philo
{
	int				params[PARAMS];
	int			    stats[STATS];
    pthread_t       thread;
    pthread_mutex_t *lfork;
    pthread_mutex_t *rfork;
}	t_phil;

typedef struct	table
{
	int				params[PARAMS];
	int				simulation[SIMULATION];
	pthread_mutex_t	*fork;
	struct	philo	*philo;
}	t_tabl;

#endif
