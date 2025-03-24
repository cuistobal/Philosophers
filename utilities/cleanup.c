#include "philosophers.h"

//
static bool free_table(t_tabl **table)
{
    int index;

    index = 0;
    if (*table)
    {
        while (index < (*table)->params[CNT])
        {
            pthread_mutex_destroy(&(*table)->fork[index]);
            index++;
        }
        if ((*table)->fork)
        {
            free((*table)->fork);
            (*table)->fork = NULL;
        }
        if ((*table)->philo)
        {
            free((*table)->philo);
            (*table)->philo = NULL; 
        }
        free(*table);
        *table = NULL;
    }
    return (false);
}

//Include va_args here
bool    cleanup(t_tabl **table, ...)
{
    char    *str;
    va_list args;

    va_start(args, table);
    str = va_arg(args, char *);
    while (str)
    {
        printf("%s ", str);
        str = va_arg(args, char *);
    }
    printf("\n");
    va_end(args);
    return (free_table(table));
}
