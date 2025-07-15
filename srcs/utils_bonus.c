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

/*
char	*read_line(void)
{
	char	*line;
	char	*tmp;
	char	buf;
	int		i;

	line = malloc(1);
	if (!line)
		return (NULL);
	line[0] = '\0';
	i = 0;
	while (read(0, &buf, 1) > 0)
	{
		tmp = malloc(i + 2);
		if (!tmp)
			return (free(line), NULL);
		for (int j = 0; j < i; j++)
			tmp[j] = line[j];
		tmp[i] = buf;
		tmp[i + 1] = '\0';
		free(line);
		line = tmp;
		if (buf == '\n')
			break ;
		i++;
	}
	if (i == 0 && buf != '\n')
		return (free(line), NULL);
	return (line);
}
	*/

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

