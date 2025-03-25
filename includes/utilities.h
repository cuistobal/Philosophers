#ifndef UTILITIES_H
# define UTILITIES_H

int			my_atoi(char *argv);

bool    	cleanup(t_tabl **table, ...);

suseconds_t	get_timestamp(void);

void		status(t_phil *philosopher, char *message);

#endif
