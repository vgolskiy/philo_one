#include "phil.h"

static int	ate_enougth(t_st *st)
{
	st->stop = true;
	print_message(&(st->ph[st->qty - 1]), 5);
	if (pthread_mutex_unlock(&st->mutex_death))
		return (error(13));
	return (EXIT_SUCCESS);
}

int			eat_some(t_ph *ph)
{
	uint64_t	curr_time;

	ph->eating = true;
	if ((curr_time = current_time()) == 1)
		return (EXIT_FAILURE);
	ph->time_limit_life = curr_time + ph->st->time_die;
	if (!ph->st->stop)
		print_message(ph, 3);
	usleep(ph->st->time_eat * 1000);
	ph->eat_qty++;
	ph->eating = false;
	if (ph->number + 1 == ph->st->qty
		&& ph->eat_qty == ph->st->eat_max)
		return (ate_enougth(ph->st));
	return (EXIT_SUCCESS);
}

int			take_forks(t_ph *ph)
{
	if (pthread_mutex_lock(&ph->st->mutex_forks[ph->fork_left]))
		return (error(18));
	if (!ph->st->stop)
		print_message(ph, 4);
	if (pthread_mutex_lock(&ph->st->mutex_forks[ph->fork_right]))
		return (error(18));
	if (!ph->st->stop)
		print_message(ph, 4);
	return (EXIT_SUCCESS);
}

int			place_forks(t_ph *ph)
{
	if (!ph->st->stop)
		print_message(ph, 2);
	if (pthread_mutex_unlock(&ph->st->mutex_forks[ph->fork_left]))
		return (error(19));
	if (pthread_mutex_unlock(&ph->st->mutex_forks[ph->fork_right]))
		return (error(19));
	usleep(ph->st->time_sleep * 1000);
	return (EXIT_SUCCESS);
}
