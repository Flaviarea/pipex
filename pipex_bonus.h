#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <stdio.h>
#include "libft/libft.h"

void	error_exit(char *msg);
char	*get_cmd_path(char *cmd, char **envp);
void	execute(char *cmd, char **envp);
void	pipex(int argc, char **argv, char **envp);
void	child_process(char *cmd, int in, int out, char **env);


#endif

