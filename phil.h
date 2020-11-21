#ifndef PHILOSO_H
# define PHILOSO_H

# include <stdio.h> // test
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef enum	e_bool
{
	false = 0,
	true = 1
}				t_bool;

typedef struct	s_err
{
	const char	*desc;
}				t_err;

typedef struct	s_ph
{
	int				turn;
	int				eats_qty;
	t_bool			fork_left;
	t_bool			fork_right;
	t_bool			eating;
	uint64_t		time_last_eat;
	uint64_t		time_limit_life;
	pthread_mutex_t	mutex;
	pthread_mutex_t	mutex_eat;
	struct s_st		*status;
}				t_ph;

typedef struct	s_st
{
	int				qty;
	int				eats_max;
	uint64_t		time_die;
	uint64_t		time_eat;
	uint64_t		time_sleep;
	uint64_t		time_start;
	pthread_mutex_t	mutex_death;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	*mutex_forks;
	struct s_ph		*ph;
}				t_st;

/*
** SUPPORT1
*/
int			error(int errn);
void		*error_ptr(int errn);
uint64_t	ft_atoi(const char *s);

/*
** SUPPORT2
*/
int			ft_strlen(const char *s);
int			ft_isdigit(int c);
int			free_all(t_st *st);

/*
** PARSE & INITIALIZE
*/
int			parse_args(t_st *st, int argc, char **argv);

#endif
