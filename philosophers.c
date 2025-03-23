#include "philosophers.h"

static void	insert_philo(t_phil **head,t_phil **tail, t_phil **new)
{
	if (!*head)
	{
		*head = *new;
		*tail = *head;
		(*new)->next = *tail;
		(*new)->prev = *tail;
	}
	else
	{
		(*head)->prev = *new;
		(*tail)->next = *new;
		(*new)->prev = *tail;
		(*new)->next = *head;
		*tail = *new;
	}
}

static bool	create_philo_node(t_phil **new, int *pos)
{
	*new = (t_phil *)malloc(sizeof(t_phil));
	if (*new)
	{
		(*new)->stats[POSTN] = *pos;
		(*new)->prev = NULL;
		(*new)->next = NULL;
		(*pos)++;
	}
	return (*new);
}

static bool	append_philos(t_tabl **table)
{
	int		pos;
	t_phil	*new;
	t_phil	*tail;

	pos = 1;
	new = NULL;
	tail = NULL;
	if (*table)
	{
		while (pos <= (*table)->params[CNT])
		{
			if (!create_philo_node(&new, &pos))
			//	cleanup();
				exit(-1);
			insert_philo(&(*table)->philo, &tail, &new);
		}
	}
	return (*table);
}

static bool	append_params(t_tabl **table, char **argv)
{
	int	temp;
	int	index;

	temp = 0;
	index = 0;
	if (*table)
	{
		while (index < PARAMS)
		{
			temp = my_atoi(argv[index]);
			if (temp < 0)
				return (free(*table), *table = NULL, false);		
			(*table)->params[index] = my_atoi(argv[index]);	
			index++;
		}
		(*table)->philo = NULL;
	}
	return (*table);
}

//
static bool	init_table(t_tabl **table, char **argv)
{
	*table = (t_tabl *)malloc(sizeof(t_tabl));
	if (*table)
	{
		if (!append_params(table, argv))
			return (false);
		return (append_philos(table));
	}
	return (*table);
}

//
int	main(int argc, char **argv)
{
	t_tabl	*table;

	table = NULL;
	if (argc == 5 || argc == 6)
	{
		if (init_table(&table, argv + 1))
		{
			/*
			t_phil	*prev = NULL;
			
			for (int i = 0; i < PARAMS; i++)
				printf("%d\n", table->params[i]);
			printf("\n");
			for (int i = 0; i < table->params[CNT]; i++)
			{
				if (table->philo)
				{
					printf("%d\n", table->philo->stats[POSTN]);
					prev = table->philo;
					table->philo = table->philo->next;
					free(prev);
					prev = NULL;
				}
			}
			if (prev)
			{
				free(prev);
				prev = NULL;
			}
			free(table);
			*/
			
		}
		return 0;
	}
	return (printf("%s\n", ARGC));
}
