#ifndef EXECUTION_H
# define EXECUTION_H

bool	init_table(t_tabl **table, char **argv);

bool	alive_and_not_full(t_tabl *table);
bool	the_show_must_go_on(t_phil *philosopher);

void    *routine(void *arg);

inline static bool	you_are_dead(t_phil	*philo)
{
	return ((get_timestamp() - philo->last_meal) < 0);
}

#endif
