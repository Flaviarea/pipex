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

#include "pipex_mandatory.h"

/*
    get_cmd_path:
	If the command contains a slash (‘/’), try running it directly (useful for ./a.out or /bin/ls).
    Otherwise, look for the command in the directories listed in the PATH environment variable.
    It returns the full path if found, otherwise NULL.
    Added debug messages to follow the flow.
*/

char	*get_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	char	*tmp;
	int		i;

	i = 0;
	// DEBUG: controllo se il comando contiene uno slash
	if (ft_strchr(cmd, '/'))
	{
		write(2, "DEBUG: command contains '/': ", 28);
		write(2, cmd, ft_strlen(cmd));
		write(2, "\n", 1);
		if (!access(cmd, X_OK))
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	// DEBUG: cerca la variabile PATH
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
	{
		write(2, "DEBUG: PATH not found in envp\n", 29);
		return (NULL);
	}
	// DEBUG: split della PATH
	paths = ft_split(envp[i] + 5, ':');
	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		// DEBUG: prova questo path
		write(2, "DEBUG: trying path: ", 21);
		write(2, path, ft_strlen(path));
		write(2, "\n", 1);
		if (!access(path, X_OK))
		{
			write(2, "DEBUG: found executable: ", 25);
			write(2, path, ft_strlen(path));
			write(2, "\n", 1);
			free_split(paths);
			return (path);
		}
		free(path);
	}
	write(2, "DEBUG: command not found in PATH\n", 32);
	free_split(paths);
	return (NULL);
}

/*
	child_process:
	Prints a debug message at startup.
	Redirects input/output.
	Closes descriptor files that are no longer needed.
	Executes the requested command via the execute function.
*/

void child_process(char *cmd, int in, int out, char **env)
{
    write(1, "Child starting...\n", 18);
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
	int	i;
	
	i = 0;
	while (arr && arr[i])
		free(arr[i++]);
	free(arr);
}

/*
	Divides the command string into arguments.
	Searches for the executable path.
	Handles the error if the command does not exist.
	Executes the command with execve.
	If execve fails, prints error and terminates.
*/

void	execute(char *cmd, char **envp)
{
	char	**args;
	char	*path;
	//int		i;

	args = ft_split(cmd, ' ');
	if (!args || !args[0] || !args[0][0])
	{
		write(2, "command not found: ", 20);
		if (args && args[0])
			write(2, args[0], ft_strlen(args[0]));
		write(2, "\n", 1);
		free_split(args);
		exit(127);
	}
	path = get_cmd_path(args[0], envp);
	if (!path)
	{
		write(2, "command not found: ", 20);
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
