#include "phil.h"

void	ft_putchar_fd(char c, int fd)
{
	if (fd)
		write(fd, &c, 1);
	return ;
}

void	ft_putstr_fd(const char *s, int fd)
{
	int i;

	if ((s) && (fd))
	{
		i = 0;
		while (s[i] != '\0')
		{
			ft_putchar_fd(s[i], fd);
			i++;
		}
	}
	return ;
}

void	ft_putnbr_fd(int n, int fd)
{
	if (fd)
	{
		if (n == -2147483648)
		{
			ft_putchar_fd(45, fd);
			ft_putchar_fd(50, fd);
			ft_putnbr_fd(147483648, fd);
		}
		else if (n >= 0)
		{
			if (n >= 10)
				ft_putnbr_fd(n / 10, fd);
			ft_putchar_fd((n % 10) + '0', fd);
		}
		else
		{
			ft_putchar_fd('-', fd);
			ft_putnbr_fd(-n, fd);
		}
	}
	return ;
}
