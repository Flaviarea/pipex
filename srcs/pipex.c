/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frea <frea@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:55:01 by frea              #+#    #+#             */
/*   Updated: 2025/08/01 13:42:12 by frea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	start_child1(char **argv, char **envp, int *fd, int infile)
{
	close(fd[0]);
	child_process(argv[2], infile, fd[1], envp);
}

static void	start_child2(char **argv, char **envp, int *fd, int outfile)
{
	close(fd[1]);
	child_process(argv[3], fd[0], outfile, envp);
}

void	pipex(char **argv, char **envp, pid_t *pid1, pid_t *pid2)
{
	int	fd[2];
	int	infile;
	int	outfile;

	infile = open(argv[1], O_RDONLY);
	outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (outfile < 0)
		error_exit("outfile open");
	if (pipe(fd) == -1)
		error_exit("pipe");
	*pid1 = fork();
	if (*pid1 < 0)
		error_exit("fork");
	  if (*pid1 == 0)
    {
        if (infile < 0)
            perror(argv[1]);  
        start_child1(argv, envp, fd, infile);
    }
	*pid2 = fork();
	if (*pid2 < 0)
        error_exit("fork");
	if (*pid2 == 0)
		start_child2(argv, envp, fd, outfile);
	if (infile >= 0)
        close(infile);
	close(outfile);
	close(fd[0]);
	close(fd[1]);
}
