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

#include "pipex_bonus.h"
#include "pipex_mandatory.h"

char	*get_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	char	*tmp;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!access(path, X_OK))
		{
			free_split(paths);
			return (path);
		}
		free(path);
	}
	free_split(paths);
	return (NULL);
}

void child_process(char *cmd, int in, int out, char **env)
{
    write(2, "Child starting...\n", 18);
    if (dup2(in, STDIN_FILENO) < 0 || dup2(out, STDOUT_FILENO) < 0)
        error_exit("dup2");
    close(in);
    close(out);
    execute(cmd, env);
}

void	error_exit(char *msg)
{
	perror(msg);
	exit(1);
}


void	free_split(char **arr)
{
	int	i = 0;
	while (arr && arr[i])
		free(arr[i++]);
	free(arr);
}

/*
    execute: parsing the string:
    Prendere argv[i] (es. "ls -l")
    Dividerlo in char **args con ft_split(cmd, ' ')
    Cercare il path eseguibile di args[0] (es. ls) → con get_cmd_path
    Eseguire il comando con execve
*/

void	execute(char *cmd, char **envp)
{
	char	**args;
	char	*path;
	//int		i;

	args = ft_split(cmd, ' ');
	if (!args || !args[0])
		error_exit("split failed or empty command");
	path = get_cmd_path(args[0], envp);
	if (!path)
	{
		write(2, "command not found: ", 19);
		write(2, args[0], ft_strlen(args[0]));
		write(2, "\n", 1);
		free_split(args);
		exit(127);
	}
	execve(path, args, envp);
	perror("execve");
	free(path);
	free_split(args);
	exit(1);
}
