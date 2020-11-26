#include "phil.h"

int		eat_some(t_ph *ph)
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
	if (pthread_mutex_unlock(&ph->mutex_eat))
		return (error(17));
	return (EXIT_SUCCESS);
}

int		take_forks(t_ph *ph)
{
	if (pthread_mutex_lock(&ph->st->mutex_forks[ph->fork_left]))
		return (error(18));
	if (!ph->st->stop)
		print_message(ph, 4);
	if (pthread_mutex_lock(&ph->st->mutex_forks[ph->fork_right]))
		return (error(18));
	if (!ph->st->stop)
		print_message(ph, 5);
	return (EXIT_SUCCESS);
}

int		place_forks(t_ph *ph)
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
