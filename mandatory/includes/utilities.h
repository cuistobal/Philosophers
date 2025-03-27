#ifndef UTILITIES_H
# define UTILITIES_H

int		my_atoi(char *argv);

bool    cleanup(t_tabl **table, ...);

long	get_timestamp(void);

void	status(t_phil *philosopher, char *message);

void	set_value(pthread_mutex_t *mutex, void **value, void *new);
void	*access_value(pthread_mutex_t *mutex, void *value);

inline static bool	you_are_dead(t_phil	*philo)
{
	return ((get_timestamp() - philo->stats[LMEAL]) < 0);
}

#endif
