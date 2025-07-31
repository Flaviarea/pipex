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

#include "pipex.h"

/*
    pipex
    Opens input/output files and checks for errors.
    Creates a pipe.
    Makes two forks: the first child executes the first command, the second child the second command.
    Each child closes the fd's it does not use and calls child_process.
    The father closes everything and waits for the children.
*/

void pipex(char **argv, char **envp, pid_t *pid1, pid_t *pid2)
{
    int     fd[2];
    int     infile;
    int     outfile;
    
    infile = open(argv[1], O_RDONLY);
    outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (infile < 0)
        error_exit("infile open");
    if (outfile < 0)
        error_exit("outfile open");
    if (pipe(fd) == -1)
        error_exit("pipe");
    *pid1 = fork();
    if (*pid1 < 0)
        error_exit("fork");
    if (*pid1 == 0)
    {
        close(fd[0]);
        child_process(argv[2], infile, fd[1], envp);
    }
    *pid2 = fork();
    if (*pid2 == 0)
    {
        close(fd[1]);
        child_process(argv[3], fd[0], outfile, envp);
    }
    close(infile);
    close(outfile);
    close(fd[0]);
    close(fd[1]);
}


