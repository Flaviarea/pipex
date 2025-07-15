/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_mandatory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frea <frea@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:45:52 by frea              #+#    #+#             */
/*   Updated: 2025/06/18 17:45:53 by frea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_mandatory.h"

/*
    mandatory:
    gestisce due comandi fissi
    retun 1 se non ci sono 4 argomenti 
*/

int	main(int argc, char **argv, char **envp)
{
	int		status1;
	int		status2;
	pid_t	pid1;
	pid_t	pid2;

	if (argc != 5)
	{
		write(2, "Usage: ./pipex infile cmd1 cmd2 outfile\n", 41);
		return (1);
	}
	int fd[2];
	if (pipe(fd) == -1)
		error_exit("pipe");
	pid1 = fork();
	if (pid1 == 0)
	{
		int infile = open(argv[1], O_RDONLY);
		if (infile < 0)
		{
			perror(argv[1]);
			infile = open("/dev/null", O_RDONLY);
			if (infile < 0)
				exit(1);
		}
		dup2(infile, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(infile);
		close(fd[0]);
		close(fd[1]);
		execute(argv[2], envp);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		int outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (outfile < 0)
		{
			perror(argv[4]);
			exit(1);
		}
		dup2(fd[0], STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
		close(fd[0]);
		close(fd[1]);
		execute(argv[3], envp);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	if (WIFEXITED(status2))
		return (WEXITSTATUS(status2));
	return (1);
}