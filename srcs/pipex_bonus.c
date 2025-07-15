/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frea <frea@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:13:32 by frea              #+#    #+#             */
/*   Updated: 2025/06/17 13:13:35 by frea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "pipex_mandatory.h"

void	handle_here_doc(char *limiter, int *fd)
{
	char	*line;
	int		tmp[2];

	if (pipe(tmp) == -1)
		error_exit("pipe");
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = read_line();
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

void	pipex_bonus(int argc, char **argv, char **env)
{
	int		i;
	int		pipefd[2];
	int		pid;
	int		fd;
	int		prev;

	prev = open(argv[1], O_RDONLY);
	if (prev < 0)
		error_exit("infile");
	i = 2;
	while (i < argc - 2)
	{
		if (pipe(pipefd) < 0)
			error_exit("pipe");
		pid = fork();
		if (pid == 0)
			child_process(argv[i], prev, pipefd[1], env);
		close(pipefd[1]);
		close(prev);
		waitpid(pid, NULL, 0);
		prev = pipefd[0];
		i++;
	}
	fd = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		error_exit("outfile");
	if (fork() == 0)
		child_process(argv[argc - 2], prev, fd, env);
	close(prev);
	close(fd);
	wait(0);
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
