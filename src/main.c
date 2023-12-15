/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:27:46 by aulicna           #+#    #+#             */
/*   Updated: 2023/12/15 16:23:00 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"

/**
 * @brief	This function is executed within the child process that
 * the pipex_handler function launches. It prepares the child process to read
 * from the infile and send its output to the pipe. It then executes
 * the specified command, ensuring that its input and output are correctly 
 * set up for the pipeline.
 * 
 * The infile is opened in read-only setup (O_RDONLY) and will be automatically
 * closed when a new program is executed using execve (__O_CLOEXEC). The file
 * permissions are set to read, write, and execute for the owner, and no 
 * permissions for others (0777).
 * 
 * Then the file descriptor of the write end of the pipe (pipex->pipe[1]) is 
 * duplicated into the standard output file descriptor (STDOUT_FILENO). This
 * connects the standard output of the child process to the write end of
 * the pipe, allowing it to send its output to the pipe.
 * 
 * Then the original file descriptor for the write end of the pipe is closed
 * since it's no longer needed.
 * 
 * Then the file descriptor of the infile (pipex->infile) is duplicated into 
 * the standard input file descriptor (STDIN_FILENO). This connects the standard 
 * input of the child process to the infile, allowing it to read from the file.
 * 
 * Then the file descriptor for the read end of the pipe is closed since it's
 * not used.
 * 
 * Finally the infile file is closed to release the file resource.
 * 
 * @param	pipex	pipex struct
 * @param	argv
 * @param	env		environment (global) variables that can be accessed by 
 * 					a program to obtain information about system's environment,
 * 					user, and configuration
*/

static void	child_process(t_pipex *pipex, char **argv, char *env[])
{
	pipex->infile = open(argv[1], O_RDONLY | __O_CLOEXEC, 0777);
	if (pipex->infile == -1)
		pipex_error();
	dup2(pipex->pipe[1], STDOUT_FILENO);
	close(pipex->pipe[1]);
	dup2(pipex->infile, STDIN_FILENO);
	close(pipex->pipe[0]);
	close(pipex->infile);
	execute_command(pipex, pipex->cmd1, env);
}

/**
 * @brief	This function is executed in the parent process. It prepares 
 * the parent process to read from the pipe and send its output to the outfile. 
 * It then executes the specified command, ensuring that its input and output 
 * are correctly set up for the pipeline. 
 * 
 * The outfile is opened for writing (O_WRONLY) and truncated to a lenght
 * of 0 (O_TRUNC). If the outfile doesn't exists, it's created (O_CREAT). 
 * It'll also be automatically closed when a new program is executed using 
 * execve (__O_CLOEXEC). The file permissions are set to read, write, and 
 * execute for the owner, and no permissions for others (0777).
 * 
 * Then the file descriptor of the read end of the pipe (pipex->pipe[0]) is 
 * duplicated to standard input (STDIN_FILENO), so that the second command can
 * read input from the pipe. 
 * 
 * Then the original pipe descriptor for read end of the pipe is closed since
 * it's no longer needed.
 * 
 * Then the file descriptor of the outfile (pipex->outfile) is duplicated
 * to standard output (STDOUT_FILENO), which redirects the output of the command 
 * to the specified outfile. 
 * 
 * Then the write end of the pipe (pipex->pipe[1]) is closed since it's not used.
 * 
 * Finally the outfile is closed to release file resources.
 * 
 * @param	pipex	pipex struct
 * @param	argv
 * @param	env		environment (global) variables that can be accessed by 
 * 					a program to obtain information about system's environment,
 * 					user, and configuration
*/

static void	parent_process(t_pipex *pipex, char **argv, char *env[])
{
	pipex->outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC
			| __O_CLOEXEC, 0664);
	if (pipex->outfile == -1)
		pipex_error();
	dup2(pipex->pipe[0], STDIN_FILENO);
	close(pipex->pipe[0]);
	dup2(pipex->outfile, STDOUT_FILENO);
	close(pipex->pipe[1]);
	close(pipex->outfile);
	execute_command(pipex, pipex->cmd2, env);
}

/**
 * @brief	This function creates a pipe, forks a child process, and manages
 * the execution of both child_process and parent_process. The waitpid function
 * ensures that the parent process waits for the child process to complete.
 * 
 * @param	pipex	pipex struct
 * @param	argv
 * @param	env		environment (global) variables that can be accessed by 
 * 					a program to obtain information about system's environment,
 * 					user, and configuration
*/

static int	pipex_handler(t_pipex *pipex, char **argv, char *env[])
{
	if (pipe(pipex->pipe) == -1)
		pipex_error();
	pipex->pid = fork();
	if (pipex->pid == -1)
		pipex_error();
	if (pipex->pid == 0)
		child_process(pipex, argv, env);
	parent_process(pipex, argv, env);
	waitpid(pipex->pid, NULL, 0);
	return (0);
}

/**
 * @brief	This function parses the command-line arguments and environment
 * variables to initialize data needed for the program execution.
 * 
 * @param	pipex	pipex struct
 * @param	argv
 * @param	env		environment (global) variables that can be accessed by 
 * 					a program to obtain information about system's environment,
 * 					user, and configuration
*/

static void	process_input(t_pipex *pipex, char **argv, char *env[])
{
	pipex->cmd1 = ft_split(argv[2], ' ');
	pipex->cmd2 = ft_split(argv[3], ' ');
	pipex->env_path = get_path(env);
	pipex->paths = ft_split(pipex->env_path, ':');
}

/**
 * @brief	The main checks for the correct number of command-line arguments.
 * If it's incorrect usage instructions are provided. Otherwise the input
 * arguments are processed, pipex process launched and finally any dynamically
 * allocated memory freed.
 * 
 * @param	argc
 * @param	argv
 * @param	env	environment (global) variables that can be accessed by a program
 * 				to obtain information about system's environment, user,
 * 				and configuration
*/

int	main(int argc, char **argv, char *env[])
{
	t_pipex	pipex;

	if (argc != 5)
	{
		ft_putstr_fd("Input error: Wrong number of arguments received.\n\n", 2);
		ft_putstr_fd("Correct usage: ./pipex infile cmd1 cmd2 outfile\n", 2);
		exit(0);
	}
	process_input(&pipex, argv, env);
	pipex_handler(&pipex, argv, env);
	ft_free(&pipex);
	return (0);
}
