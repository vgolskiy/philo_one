#include "phil.h"

t_bool		ft_isdigit(int c)
{
	if ((c >= 48) && (c <= 57))
		return (true);
	return (false);
}

int			ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (s)
		while (s[i])
			i++;
	return (i);
}

int			free_all(t_st *st)
{
	if (st->ph)
		free(st->ph);
	if (st->mutex_forks)
		free(st->mutex_forks);
	return (EXIT_SUCCESS);
}

uint64_t	current_time(void)
{
	uint64_t				res;
	static struct timeval	time;

	if (gettimeofday(&time, 00))
		return (error(10));
	res = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (res);
}
