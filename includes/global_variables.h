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
# define PHILO "Philosopher"
# define THINK "starts thinking."
# define LFORK "takes left fork."
# define RFORK "takes right fork."
# define EATS "starts eating."
# define SLEEP "starts sleeping."
# define DIES "dies."

//Error messages
# define ARGC "Usage: ./philosophers philos die eat sleep [min eat].\n"
# define ATOI "Invalid parameter.\n"
# define THREAD_CREATE "Failed to create Thread.\n"
# define INIT_TABLE "Failed to initialise the simulaiton.\n"

//Misc
# define SUCCESS "Greaaaaat suucceeeeeees.\n"

#endif
