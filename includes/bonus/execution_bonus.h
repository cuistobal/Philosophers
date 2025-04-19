#ifndef EXECUTION_H
# define EXECUTION_H

int		routine(t_phil *philo);

bool	init_table(t_tabl **table, char **argv);

bool	create_child_process(t_phil *philo);

void	eating(t_phil *philosopher);
void	sleeping(t_phil *philosopher);
void	thinking(t_phil *philosopher);

#endif
