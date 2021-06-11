#include "libft.h"

int	ft_putstr_fd(const char *str, int fd)
{
	int	i;

	i = -1;
	while (str[++i])
		ft_putchar_fd(str[i], fd);
	return (i);
}