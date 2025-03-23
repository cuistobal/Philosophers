#include "philosophers.h"

bool	init_table(t_tabl *table, char **args)
{
	int	index;

	index = 0;
	table = (t_tabl *)malloc(sizeof(t_tabl));
	if (table)
	{
		while (index < PARAMS)
		{
			if (!argv[index])

			table->params[index] = argv[index];
		}
		return (true);
	}
	return (false);
}

int	main(int argc, char **argv)
{
	int	philocount;
	int	die;
	int eat;
	int sleep;
	int optional;

	t_tabl	table;

	if (argc == 5 || argc == 6)
	{
		init_table(&table, argv + 1);
	}
}
