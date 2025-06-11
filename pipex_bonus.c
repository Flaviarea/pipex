#include "pipex_bonus.h"

void	child_process(char *cmd, int in, int out, char **env)
{
	if (dup2(in, 0) < 0 || dup2(out, 1) < 0)
		error_exit("dup2");
	execute(cmd, env);
}

void	pipex(int argc, char **argv, char **env)
{
	int		i, pipefd[2], pid, fd, prev;

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