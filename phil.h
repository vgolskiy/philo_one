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

typedef struct	s_msg
{
	const char	*desc;
}				t_msg;

typedef struct	s_ph
{
	int				number;
	int				eat_qty;
	t_bool			fork_left;
	t_bool			fork_right;
	t_bool			eating;
	uint64_t		time_limit_life;
	pthread_mutex_t	mutex_eat;
	struct s_st		*st;
}				t_ph;

typedef struct	s_st
{
	int				qty;
	int				eat_max;
	t_bool			stop;
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
t_bool		ft_isdigit(int c);
int			free_all(t_st *st);
uint64_t	current_time(void);

/*
** SUPPORT3
*/
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(const char *s, int fd);
void		ft_putnbr_fd(int n, int fd);

/*
** PARSE & INITIALIZE
*/
int			parse_args(t_st *st, int argc, char **argv);

/*
**	PARALLELIZE
*/
int			parallelize(t_st *st);

/*
**	EAT WITH FORKS
*/
int			eat_some(t_ph *ph);
int			take_forks(t_ph *ph);
int			place_forks(t_ph *ph);

/*
**	PRINT MESSAGE
*/
int			print_message(t_ph *ph, int msg_num);

#endif
