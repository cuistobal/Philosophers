#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct	table
{
	pthread_mutex_t	*fork;
	struct	philo	*philo;
	pthread_mutex_t	monitoring;
	long			params[TABLES];
}	t_tabl;

typedef struct	philo
{
    pthread_t       thread;
	pthread_mutex_t *lfork;
    pthread_mutex_t *rfork;
	struct	table	*table;
	long		    stats[STATS];
}	t_phil;

#endif
