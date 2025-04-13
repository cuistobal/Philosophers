#ifndef EXECUTION_H
# define EXECUTION_H

bool	init_table(t_tabl **table, char **argv);

bool    create_child_process(t_tabl *table, int index);
//bool	create_child_process(t_phil *philo, pid_t *pid);

#endif
