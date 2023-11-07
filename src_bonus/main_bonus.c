/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:27:46 by aulicna           #+#    #+#             */
/*   Updated: 2023/11/07 07:38:01 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex_bonus.h"

/**
 * @brief	This function handles the child process execution. It prepares the
 * command, sets up redirection to the pipe's write end, executes the command,
 * and frees any dynamically allocated memory. 
 * 
 * @param	pipex	pipex struct
 * @param	argv
 * @param	env		environment (global) variables that can be accessed by 
 * 					a program to obtain information about system's environment,
 * 					user, and configuration
*/

static void	child_process(t_pipex *pipex, char *argv, char *env[])
{
	pipex->cmd = ft_split(argv, ' ');
	dup2(pipex->pipe[1], STDOUT_FILENO);
	close(pipex->pipe[0]);
	execute_command(pipex, pipex->cmd, env);
	free_array(pipex->cmd);
}

/**
 * @brief	This function handles the parent process execution. It sets up
 * redirection to the pipe's read end, waits for the child process to finish,
 * and ensures the output flows through the pipe for further processing.
 * 
 * @param	pipex	pipex struct
 * @param	argv
 * @param	env		environment (global) variables that can be accessed by 
 * 					a program to obtain information about system's environment,
 * 					user, and configuration
*/

void	parent_process(t_pipex *pipex)
{
	dup2(pipex->pipe[0], STDIN_FILENO);
	close(pipex->pipe[1]);
	waitpid(pipex->pid, NULL, 0);
}

/**
 * @brief	This function creates a pipe, forks a child process, and manages
 * the execution of both child_process and parent_process. 
 * 
 * @param	pipex	pipex struct
 * @param	argv
 * @param	env		environment (global) variables that can be accessed by 
 * 					a program to obtain information about system's environment,
 * 					user, and configuration
*/

static int	pipex_handler(t_pipex *pipex, char *argv, char *env[])
{
	if (pipe(pipex->pipe) == -1)
		pipex_error();
	pipex->pid = fork();
	if (pipex->pid == -1)
		pipex_error();
	if (pipex->pid == 0)
		child_process(pipex, argv, env);
	else
		parent_process(pipex);
	return (0);
}

/**
 * @brief	The main checks for the correct number of command-line arguments.
 * If it's incorrect usage instructions are provided. Otherwise the input
 * arguments are processed and then the pipex process launched. 
 * 
 * It executes one less time than the number of provided cmd arguments is 
 * always passing the output to the read end of the pipe. 
 * 
 * Once the last cmd argument is encountered the output is redirected to
 * the outfile by duplicating the file descriptor pipex.outfile and associating
 * it with the standard output filde descriptor (STDOUT_FILENO).
 * 
 * Finally any dynamically allocated memory is freed.
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
	int		i;

	if (argc < 5)
		no_valid_argument();
	i = process_input(&pipex, argc, argv, env);
	while (i < argc - 2)
	{
		pipex_handler(&pipex, argv[i], env);
		i++;
	}
	pipex.cmd = ft_split(argv[argc - 2], ' ');
	dup2(pipex.outfile, STDOUT_FILENO);
	execute_command(&pipex, pipex.cmd, env);
	free_array(pipex.cmd);
	free_array(pipex.paths);
	return (0);
}
