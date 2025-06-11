//#include "../include/pipex.h"


/*< file1 ls -l | grep .c | wc -l > file2 
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
	pipex(argc, argv, envp);
	return (0);
}
