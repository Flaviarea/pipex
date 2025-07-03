#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <stdio.h>
# include "libft/libft.h"
# include "pipex_mandatory.h"

void	pipex_bonus(int argc, char **argv, char **envp);
void	handle_here_doc(char *limiter, int *fd);
char	*read_line(void);

#endif

