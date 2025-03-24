#include "philosophers.h"

//
int	main(int argc, char **argv)
{
	t_tabl			*table;

	table = NULL;
	if (argc == 5 || argc == 6)
	{
		if (init_table(&table, argv + 1))
		{
		//	lets_get_this_party_started(table);
		//	the_show_must_go_on(table);
	        (cleanup(&table, NULL));	
        }
		return (cleanup(&table, INIT_TABLE));
	}
	return (printf("%s\n", ARGC));
}
