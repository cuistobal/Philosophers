#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct	fork
{
	bool	status;
}	t_fork;

typedef struct	philo
{
	int				stats[STATS];
	struct	fork	*fork;
	struct	philo	*next;
	struct	philo	*prev;
}	t_phil;

typedef struct	table
{
	int				params[PARAMS];
	struct	philo	*philo;
}	t_tabl;

#endif
