/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frea <frea@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:12:46 by frea              #+#    #+#             */
/*   Updated: 2025/06/17 13:12:49 by frea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
< file1 ls -l | grep .c | wc -l > file2 
argv[1] = file1

argv[2] = cmd1 = "ls -l"

argv[3] = cmd2 = "grep .c"

argv[4] = cmd3 = "wc -l"

argv[5] = file2

*/

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	if (argc < 5)
	{
		write(2, "Usage: ./pipex file1 cmd1 cmd2 ... file2\n", 42);
		return (1);
	}
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		handle_here_doc[argv[2], fd);
	else
		pipex_bonus(argc, argv, envp);
	return (0);
}
