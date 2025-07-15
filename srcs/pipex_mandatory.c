/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frea <frea@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:55:01 by frea              #+#    #+#             */
/*   Updated: 2025/06/18 16:55:03 by frea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_mandatory.h"

void pipex_mandatory(char **argv, char **envp)
{
    int     fd[2];
    int     infile;
    int     outfile;
    pid_t   pid1;
    pid_t	pid2;
    
    infile = open(argv[1], O_RDONLY);
    outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (infile < 0)
    {
    	perror("infile open");
    	exit(1);
    }
    if (outfile < 0)
     {
    	perror("outfile open");
    	exit(1);
    }
    if (pipe(fd) == -1)
        error_exit("pipe");
    pid1 = fork();
    if (pid1 < 0)
	error_exit("fork");
    if (pid1 == 0)
    {
    	close(fd[0]);
        child_process(argv[2], infile, fd[1], envp);
    }
    pid2 = fork();
    if (pid2 == 0)
    {
    	close(fd[1]);
        child_process(argv[3], fd[0], outfile, envp);
    }
    close(infile);
    close(outfile);
    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}


