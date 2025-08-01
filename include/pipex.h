/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frea <frea@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 13:30:19 by frea              #+#    #+#             */
/*   Updated: 2025/08/01 13:30:22 by frea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <stdio.h>
# include <errno.h>
# include "libft/include/libft.h"

void	error_exit(char *msg);
char	*get_cmd_path(char *cmd, char **envp);
void	execute(char *cmd, char **envp);
void	pipex(char **argv, char **envp, pid_t *pid1, pid_t *pid2);
void	child_process(char *cmd, int in, int out, char **env);
void	free_split(char **arr);
void	error_exit(char *msg);

#endif
