#include "philosophers.h"

static bool alive_and_not_full(t_tabl *table)
{
    bool    full;
    int     index;

    index = 0;
    while (index < table->params[CNT])
    {
        if ()
        index++;
    }
}
//
int	main(int argc, char **argv)
{
	t_tabl			*table;

	table = NULL;
	if (argc == 5 || argc == 6)
	{
		if (init_table(&table, argv + 1))
		{
            while (alive_and_not_full(table))
                continue ;
	        cleanup(&table, NULL);
            return 0;
        }
		return (cleanup(&table, INIT_TABLE));
	}
	return (cleanup(&table, ARGC));
//	return (printf("%s\n", ARGC));
}
