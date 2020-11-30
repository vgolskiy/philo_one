#include "phil.h"

static int	check_cycle(t_ph *ph)
{
	uint64_t	curr_time;

	while (!ph->st->stop)
	{
		if ((curr_time = current_time()) == 1)
			return (EXIT_FAILURE);
		if (!ph->st->stop && !ph->eating
			&& (curr_time > ph->time_limit_life))
		{
			ph->st->stop = true;
			print_message(ph, 6);
			break ;
		}
		usleep(777);
	}
	return (EXIT_SUCCESS);
}

static void	*check_status(void *arg)
{
	t_ph		*ph;

	ph = (t_ph *)arg;
	if (pthread_mutex_lock(&ph->st->mutex_status))
	{
		error(11);
		return ((void *)1);
	}	
	if (check_cycle(ph))
	{
		pthread_mutex_unlock(&ph->st->mutex_status);
		return ((void *)1);
	}
	if (pthread_mutex_unlock(&ph->st->mutex_status))
	{
		error(11);
		return ((void *)1);
	}
	return ((void *)0);
}

static void	*actions_cycle(t_ph *ph)
{
	if (ph->number % 2)
		usleep(ph->st->time_eat * 900);
	while (!ph->st->stop)
	{
		if (!ph->st->stop)
			if (take_forks(ph))
				return ((void *)1);
		if (!ph->st->stop)
			if (eat_some(ph))
				return ((void *)1);
		if (!ph->st->stop)
			if (place_forks(ph))
				return ((void *)1);
		if (!ph->st->stop)
			if (print_message(ph, 1))
				return ((void *)1);
	}
	return ((void *)0);
}

static void	*actions(void *arg)
{
	uint64_t	curr_time;
	t_ph		*ph;

	ph = (t_ph *)arg;
	if ((curr_time = current_time()) == 1)
		return ((void *)1);
	ph->time_limit_life = curr_time + ph->st->time_die;
	if (pthread_create(&ph->checker_id, 00, &check_status, (void *)ph))
	{
		error(12);
		return ((void *)1);
	}
	return (actions_cycle(ph));
}

int			parallelize(t_st *st)
{
	int			i;

	if ((st->time_start = current_time()) == 1)
		return (EXIT_FAILURE);
	i = -1;
	while (++i < st->qty)
	{
		if (pthread_create(&st->ph->ph_id, 00, &actions, (void *)&(st->ph[i])))
			return (error(14));
		usleep(42);
	}
	return (EXIT_SUCCESS);
}
