#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct	philo
{
	u_int64_t		params[PARAMS];
	u_int64_t	    stats[STATS];
    pthread_t       thread;
    pthread_mutex_t *lfork;
    pthread_mutex_t *rfork;
}	t_phil;

typedef struct	table
{
	u_int64_t		params[TABLES];
	pthread_mutex_t	*fork;
	struct	philo	*philo;
}	t_tabl;

#endif
