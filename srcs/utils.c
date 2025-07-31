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

char	*get_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	char	*tmp;
	int		i;

	if (ft_strchr(cmd, '/')) 
		return (ft_strdup(cmd));
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
	{
		write(2, "PATH not found in env\n", 23);
		return (NULL);
	}
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
    if (dup2(in, STDIN_FILENO) < 0 || dup2(out, STDOUT_FILENO) < 0)
        error_exit("child_process: dup2");
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
	int	i;
	
	i = 0;
	while (arr && arr[i])
		free(arr[i++]);
	free(arr);
}

/*
    execute: parsing the string:
    The function will split the command into arguments, find the executable path,
	and then execute it using execve.
	args[0] is the command to execute, args[1] is the first argument, etc.
	envp is the environment variables passed to execve.
	if the programm has successfully executed, it will not return.
	If execve fails, it will write an error message and exit with status 1.
	It is assumed that the command is a valid executable file.
*/

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
		write(2, args[0], ft_strlen(args[0]));
		write(2, ": command not found\n", 21);
		free_split(args);
		exit(127);
	}
	execve(path, args, envp);
	write(2, "execve failed\n", 15);
	free(path);
	free_split(args);
	exit(1);
}
