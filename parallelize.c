#include "phil.h"

static void	*check_status(void *arg)
{
	uint64_t	curr_time;
	t_ph		*ph;

	ph = (t_ph *)arg;
	while (!ph->st->stop)
	{
		if ((curr_time = current_time()) == 1)
			return ((void *)1);
		if (!ph->st->stop && !ph->eating
			&& (curr_time > ph->time_limit_life))
		{
			ph->st->stop = true;
			print_message(ph, 6);
			if (pthread_mutex_unlock(&ph->st->mutex_death))
			{
				error(11);
				return ((void *)1);
			}
			return ((void *)0);
		}
		usleep(666);
	}
	return ((void *)0);
}

static void	*actions_cycle(t_ph *ph)
{
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
	pthread_t	thread_id;
	uint64_t	curr_time;
	t_ph		*ph;

	ph = (t_ph *)arg;
	if ((curr_time = current_time()) == 1)
		return ((void *)1);
	ph->time_limit_life = curr_time + ph->st->time_die;
	if (pthread_create(&thread_id, 00, &check_status, (void *)ph))
	{
		error(12);
		return ((void *)1);
	}
	pthread_detach(thread_id);
	return (actions_cycle(ph));
}

int			parallelize(t_st *st)
{
	pthread_t	thread_id;
	int			i;

	if ((st->time_start = current_time()) == 1)
		return (EXIT_FAILURE);
	i = -1;
	while (++i < st->qty)
	{
		if (pthread_create(&thread_id, 00, &actions, (void *)&(st->ph[i])))
			return (error(14));
		pthread_detach(thread_id);
		usleep(42);	
	}
	return (EXIT_SUCCESS);
}
