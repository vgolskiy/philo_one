#include "phil.h"

static t_ph	*init_ph(t_st *st)
{
	t_ph	*ph;
	int		i;

	if (!(ph = (t_ph *)malloc(st->qty * sizeof(t_ph))))
		return (00);
	i = -1;
	while (++i < st->qty)
	{
		ph[i].number = i;
		ph[i].eating = false;
		ph[i].eat_qty = 0;
		ph[i].fork_left = i;
		ph[i].fork_right = (i + 1) % st->qty;
		ph[i].st = st;
	}
	return (ph);
}

static int	parse_args2(t_st *st)
{
	int	i;

	if (pthread_mutex_init(&st->mutex_status, 00)
		|| pthread_mutex_init(&st->mutex_print, 00))
		return (error(16));
	if (!(st->mutex_forks =
	(pthread_mutex_t *)malloc(st->qty * sizeof(pthread_mutex_t))))
		return (error(9));
	st->stop = false;
	i = -1;
	while (++i < st->qty)
		if (pthread_mutex_init(&st->mutex_forks[i], 00))
			return (error(16));
	return (EXIT_SUCCESS);
}

int			parse_args(t_st *st, int argc, char **argv)
{
	if ((st->qty = (int)ft_atoi(argv[1])) < 2)
		return (error(3));
	if ((st->time_die = ft_atoi(argv[2])) <= 0)
		return (error(4));
	if ((st->time_eat = ft_atoi(argv[3])) <= 0)
		return (error(5));
	if ((st->time_sleep = ft_atoi(argv[4])) <= 0)
		return (error(6));
	if (argc == 6)
	{
		if ((st->eat_max = (int)ft_atoi(argv[5])) <= 0)
			return (error(7));
	}
	else
		st->eat_max = 0;
	if (!(st->ph = init_ph(st)))
		return (error(8));
	return (parse_args2(st));
}
