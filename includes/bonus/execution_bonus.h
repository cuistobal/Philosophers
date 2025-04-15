#ifndef EXECUTION_H
# define EXECUTION_H

void	*kindergarten(void *data);

bool	init_table(t_tabl **table, char **argv);

void    create_child_process(t_tabl *table, int index);

int		routine(t_phil *philo);

void	eating(t_phil *philosopher);
void	sleeping(t_phil *philosopher);
void	thinking(t_phil *philosopher);

#endif
