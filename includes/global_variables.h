#ifndef GLOBAL_VARIABLES_H
# define GLOBAL_VARIABLES_H

//Table macros
# define PARAMS 5

# define CNT 0
# define EAT 1
# define SLP 2
# define DIE 3
# define END 4

//Philo macros
# define STATS 3

# define POSTN 0	 
# define LMEAL 1
# define EATEN 2

//Routine messages
# define THNK "is thinking\n"
# define FORK "has taken a fork\n"
# define EATS "is eating\n"
# define SLEP "is sleeping\n"
# define DIED "died\n"

//Error messages
# define ARGC "Usage: ./philosophers philos die eat sleep [min eat].\n"
# define ATOI "Invalid parameter.\n"
# define THREAD_CREATE "Failed to create Thread.\n"
# define INIT_TABLE "Failed to initialise the simulaiton.\n"

//Misc
# define SUCCESS "Greaaaaat suucceeeeeees.\n"

#endif
