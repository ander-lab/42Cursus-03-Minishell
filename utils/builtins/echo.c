#include "../../includes/minishell.h"

int	print_cmd_proc(char **cmd, int red, t_gdata *gdata)
{
	int	x;
	int	fd;

	x = 0;
	if (red < 2)
		fd = 1;
	while (cmd[x])
	{
		if (ft_strcmp(cmd[x], "$?") == 0)
		{
			ft_putnbr_fd(gdata->proc, fd);
			write(fd, "\n", 1);
			return (1);
		}
		x++;
	}
	return (0);
}
