#include "philoso.h"

static t_ph	*init_ph(t_st *st)
{
	t_ph	*ph;
	int		i;

	if (!(ph = (t_ph *)malloc(st->qty * sizeof(t_ph))))
		return (00);
	i = -1;
	while (++i < st->qty)
	{
		ph[i].turn = i;
		ph[i].eating = false;
		ph[i].eats_qty = 0;
		ph[i].fork_left = i;
		ph[i].fork_right = (i + 1) % st->qty;
		ph[i].status = st;
		if (pthread_mutex_init(&ph[i].mutex, 00)
			|| pthread_mutex_init(&ph[i].mutex_eat, 00)
			|| pthread_mutex_lock(&ph[i].mutex_eat))
			return (error_ptr(10));
	}
	return (ph);
}

static int	parse_args2(t_st *st)
{
	int	i;

	if (pthread_mutex_init(&st->mutex_death, 00)
		|| pthread_mutex_init(&st->mutex_print, 00)
		|| pthread_mutex_lock(&st->mutex_death))
		return (error(10));
	if (!(st->mutex_forks =
	(pthread_mutex_t *)malloc(st->qty * sizeof(pthread_mutex_t))))
		return (error(9));
	i = -1;
	while (++i < st->qty)
		if (pthread_mutex_init(&st->mutex_forks[i], 00))
			return (error(10));
	return (EXIT_SUCCESS);
}

int			parse_args(t_st *st, int argc, char **argv)
{
	if ((st->qty = (int)ft_atoi(argv[1])) < 2)
		return (error(3));
	if ((st->time_die = ft_atoi(argv[2])) < 0)
		return (error(4));
	if ((st->time_eat = ft_atoi(argv[3])) < 0)
		return (error(5));
	if ((st->time_sleep = ft_atoi(argv[4])) < 0)
		return (error(6));
	if (argc == 6)
	{
		if ((st->eats_max = (int)ft_atoi(argv[5])) < 0)
			return (error(7));
	}
	else
		st->eats_max = -1;
	if (!(st->ph = init_ph(st)))
		return (error(8));
	return (parse_args2(st));
}
