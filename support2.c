#include "philoso.h"

int		ft_isdigit(int c)
{
	if ((c >= 48) && (c <= 57))
		return (1);
	return (0);
}

int		ft_strlen(const char *s)
{
	int	i;
	
	i = 0;
	if (s)
		while (s[i])
			i++;
	return (i);
}

int		free_all(t_st *st)
{
	int	i;
	
	if (pthread_mutex_destroy(&st->mutex_death)
		|| pthread_mutex_destroy(&st->mutex_print))
		return (error(10));
	if (st->ph)
	{
		i = -1;
		while (++i < st->qty)
		{
			if (pthread_mutex_destroy(&st->ph[i].mutex)
				|| pthread_mutex_destroy(&st->ph[i].mutex_eat))
				return (error(10));
		}
		free(st->ph);
	}
	if (st->mutex_forks)
	{
		i = -1;
		while (++i < st->qty)
			if (pthread_mutex_destroy(&st->mutex_forks[i]))
				return (error(10));
		free(st->mutex_forks);
	}
	return (EXIT_SUCCESS);
}
