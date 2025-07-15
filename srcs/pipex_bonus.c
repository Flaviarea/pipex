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

/*
	handle_here_doc:
	Handles the here_doc feature: reads from stdin to the delimiter.
	Each line is written to a temporary pipe.
	When it finds the delimiter, it closes the write and returns the read fd.
	Used to simulate terminal input in commands with here_doc.
	Debug: prints each line read and when it finds the delimiter.
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
		line = get_next_line(STDIN_FILENO);
		write(2, "DEBUG: heredoc read line: ", 26);
		if (line)
			write(2, line, ft_strlen(line));
		if (!line || (!ft_strncmp(line, limiter, ft_strlen(limiter)) && line[ft_strlen(limiter)] == '\n'))
		{
			write(2, "DEBUG: heredoc delimiter found\n", 30);
			free(line);
			break;
		}
		write(tmp[1], line, ft_strlen(line));
		free(line);
	}
	close(tmp[1]);
	fd[0] = tmp[0];
}

/*
	pipex_bonus:
	Handles N commands sequentially via pipe (not just 2 like the mandatory).
	Opens the input file and creates a chain of processes connected by pipes.
	Each intermediate command is executed in a child, with input/output redirected.
	The last command writes to the output file.
	Debug: prints which command is executed and the descriptor files involved.
*/

void	pipex_bonus(int argc, char **argv, char **env)
{
	int		i;
	int		pipefd[2];
	int		pid;
	int		prev;
	int		last_pid;
	int		status;
	int		is_heredoc = 0;
	int status;

	// Gestione here_doc
	if (argc > 1 && ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		is_heredoc = 1;
		int herefd[2];
		handle_here_doc(argv[2], herefd);
		prev = herefd[0];
		i = 3;
	}
	else
	{
		prev = open(argv[1], O_RDONLY);
		if (prev < 0)
			prev = open("/dev/null", O_RDONLY);
		i = 2;
	}
	while (i < argc - 2)
	{
		if (pipe(pipefd) < 0)
			error_exit("pipe");
		pid = fork();
		if (pid == 0)
		{
			dup2(prev, STDIN_FILENO);
			dup2(pipefd[1], STDOUT_FILENO);
			close(prev);
			close(pipefd[0]);
			close(pipefd[1]);
			execute(argv[i], env);
			exit(127);
		}
		close(pipefd[1]);
		close(prev);
		// NON chiamare waitpid qui!
		prev = pipefd[0];
		i++;
	}
	// L'ultimo comando: il figlio apre il file di output
	last_pid = fork();
	if (last_pid == 0)
	{
		int fd;
		if (is_heredoc)
			fd = open(argv[argc - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			fd = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror(argv[argc - 1]);
			exit(1);
		}
		if (dup2(prev, STDIN_FILENO) < 0)
		{
			perror("dup2 prev");
			close(fd);
			exit(1);
		}
		if (dup2(fd, STDOUT_FILENO) < 0)
		{
			perror("dup2 fd");
			close(fd);
			exit(1);
		}
		close(prev);
		close(fd);
		execute(argv[argc - 2], env);
		exit(127); // Se execute fallisce
	}
	close(prev);
	int wstatus;
	status = -1;
	pid_t wpid;
	while ((wpid = waitpid(-1, &wstatus, 0)) > 0)
	{
		if (wpid == last_pid)
			status = wstatus;
	}
	if (status != -1 && WIFEXITED(status))
		exit(WEXITSTATUS(status));
	else if (status != -1 && WIFSIGNALED(status))
		exit(128 + WTERMSIG(status));
	exit(1);
}
