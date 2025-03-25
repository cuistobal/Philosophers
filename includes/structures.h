#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct	philo
{
    pthread_t       thread;
    pthread_mutex_t *lfork;
    pthread_mutex_t *rfork;
	u_int64_t	    stats[STATS];
	u_int64_t		params[PARAMS];
}	t_phil;

typedef struct	table
{
	pthread_mutex_t	*fork;
	struct	philo	*philo;
	pthread_mutex_t	monitoring;
	u_int64_t		params[TABLES];
}	t_tabl;

#endif
