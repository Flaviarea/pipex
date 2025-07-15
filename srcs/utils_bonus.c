#include "pipex_bonus.h"

/*
    execute: parsing the string:
    Prendere argv[i] (es. "ls -l")
    Dividerlo in char **args con ft_split(cmd, ' ')
    Cercare il path eseguibile di args[0] (es. ls) → con get_cmd_path
    Eseguire il comando con execve
*/


void	error_exit(char *msg)
{
	perror(msg);
	exit(1);
}

void	handle_here_doc(char *limiter, int *fd)
{
	char	*line;
	int		tmp[2];

	if (pipe(tmp) == -1)
		error_exit("pipe");
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(fd);
		if (!line || !ft_strncmp(line, limiter, ft_strlen(limiter)))
		{
			free(line);
			break;
		}
		write(tmp[1], line, ft_strlen(line));
		free(line);
	}
	close(tmp[1]);
	fd[0] = tmp[0];
}

