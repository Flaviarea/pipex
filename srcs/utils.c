/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frea <frea@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:13:42 by frea              #+#    #+#             */
/*   Updated: 2025/06/17 13:13:45 by frea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**get_paths_from_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
	{
		write(2, "PATH not found in env\n", 23);
		return (NULL);
	}
	return (ft_split(envp[i] + 5, ':'));
}

static char	*join_path_and_check(char *dir, char *cmd)
{
	char	*tmp;
	char	*full;

	tmp = ft_strjoin(dir, "/");
	full = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!access(full, X_OK))
		return (full);
	free(full);
	return (NULL);
}

char	*get_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;

	i = -1;
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	paths = get_paths_from_env(envp);
	if (!paths)
		return (NULL);
	while (paths[++i])
	{
		path = join_path_and_check(paths[i], cmd);
		if (path)
		{
			free_split(paths);
			return (path);
		}
	}
	free_split(paths);
	return (NULL);
}

void	child_process(char *cmd, int in, int out, char **env)
{
	if (in < 0)
    {
        close(out);
        execute(cmd, env);
        return;
    }
	if (dup2(in, STDIN_FILENO) < 0 || dup2(out, STDOUT_FILENO) < 0)
		error_exit("child_process: dup2");
	close(in);
	close(out);
	execute(cmd, env);
}

void	execute(char *cmd, char **envp)
{
	char	**args;
	char	*path;

	args = ft_split(cmd, ' ');
	if (!args || !args[0] || args[0][0] == '\0')
	{
		free_split(args);
		write(2, "command not found\n", 19);
		exit(127);
	}
	path = get_cmd_path(args[0], envp);
	if (!path)
	{
		write(2, "bash: ", 6);
		write(2, args[0], ft_strlen(args[0]));
		write(2, ": command not found\n", 21);
		free_split(args);
		exit(127);
	}
	execve(path, args, envp);
	perror(args[0]);
	free(path);
	free_split(args);
	exit(1);
}
