#include "phil.h"

void	*check_status(void *arg)
{
	uint64_t	curr_time;
	t_ph		*ph;

	ph = (t_ph *)arg;
	while (!ph->st->stop)
	{
		if (pthread_mutex_lock(&ph->mutex))
		{
			error(11);
			return ((void *)1);
		}
		if ((curr_time = current_time()) == 1)
			return ((void *)1);
		if (!ph->st->stop
			&& !ph->eating && (curr_time > ph->time_limit_life))
		{
			ph->st->stop = true;
			print_message(ph, 7);
			if (pthread_mutex_unlock(&ph->mutex)
				|| pthread_mutex_unlock(&ph->st->mutex_death))
			{
				error(11);
				return ((void *)1);
			}
			return ((void *)0);
		}
		if (pthread_mutex_unlock(&ph->mutex))
		{
			error(11);
			return ((void *)1);
		}
		usleep(1000);
	}
	return ((void *)0);
}

void	*routine(void *arg)
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
	//pthread_detach(thread_id);
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

void	*counter(void *arg)
{
	int		i;
	int		eat;
	t_st	*st;

	st = (t_st *)arg;
	eat = 0;
	while (eat < st->eat_max)
	{
		i = -1;
		while (++i < st->qty)
		{
			if (pthread_mutex_lock(&st->ph[i].mutex_eat))
			{
				error(13);
				return ((void *)1);
			}
		}
		eat++;
	}
	st->stop = true;
	print_message(&(st->ph[0]), 6);
	if (pthread_mutex_unlock(&st->mutex_death))
	{
		error(13);
		return ((void *)1);
	}
	return ((void *)0);
}

int		parallelize(t_st *st)
{
	pthread_t	thread_id;
	int			i;

	if ((st->time_start = current_time()) == 1)
		return (EXIT_FAILURE);
	if (st->eat_max)
	{
		if (pthread_create(&thread_id, 00, &counter, (void *)st))
			return (error(14));
		//pthread_detach(thread_id);
	}
	i = -1;
	while (++i < st->qty)
	{
		if (pthread_create(&thread_id, 00, &routine, (void *)&(st->ph[i])))
			return (error(14));
		//pthread_detach(thread_id);
		usleep(100);	
	}
	return (EXIT_SUCCESS);
}
