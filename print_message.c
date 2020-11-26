#include "phil.h"

/*
** MESSAGES LIST
** 1) Current time philosopher# is thinking
** 2) Current time philosopher# is sleeping
** 3) Current time philosopher# is eating
** 4) Current time philosopher# has taken a fork
** 5) Reached number of times each philosopher must eat
** 6) Current time philosopher# died
*/

t_msg	g_msg[] =
{
	{" is thinking\n"},
	{" is sleeping\n"},
	{" is eating\n"},
	{" has taken a fork\n"},
	{" Reached number of times each philosopher must eat\n"},
	{" died\n"}
};

int		print_message(t_ph *ph, int msg_num)
{
	uint64_t	curr_time;

	if (pthread_mutex_lock(&ph->st->mutex_print))
		return (error(20));
	if ((curr_time = current_time()) == 1)
		return (EXIT_FAILURE);
	ft_putnbr_fd((int)(curr_time - ph->st->time_start), STDOUT_FILENO);
	if (msg_num != 6)
	{
		ft_putchar_fd(' ', STDOUT_FILENO);
		ft_putnbr_fd(ph->number + 1, STDOUT_FILENO);
	}
	ft_putstr_fd(g_msg[msg_num - 1].desc, STDOUT_FILENO);
	if (pthread_mutex_unlock(&ph->st->mutex_print))
		return (error(20));
	return (EXIT_SUCCESS);
}
