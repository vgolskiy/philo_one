#include "phil.h"

static int	pthread_result(t_st *st)
{
	int		status;
	int		i;

	i = -1;
	while (++i < st->qty)
	{
		pthread_join(st->ph[i].ph_id, (void *)&status);
		if (status)
			return (free_all(st) && EXIT_FAILURE);
		pthread_join(st->ph[i].checker_id, (void *)&status);
		if (status)
			return (free_all(st) && EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int			main(int argc, char **argv)
{
	t_st	st;

	if (argc < 5)
		return (error(1));
	else if (argc > 6)
		return (error(2));
	else
	{
		if (parse_args(&st, argc, argv))
			return (EXIT_FAILURE);
	}
	if (parallelize(&st))
		return (free_all(&st) && EXIT_FAILURE);
	if (pthread_result(&st))
		return (EXIT_FAILURE);
	if (free_all(&st))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
