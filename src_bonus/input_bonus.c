/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 06:48:19 by aulicna           #+#    #+#             */
/*   Updated: 2024/01/29 15:31:20 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex_bonus.h"

/**
 * @brief	This function handles the execution of the program when the first
 * argument is "here_doc". A here_doc allows the user to input text 
 * interactively, terminated by a specified delimiter (limiter).
 * 
 * A pipe is set up to capture the user's input and forks a child process 
 * to read this input. The read end of the pipe is closed as the process reads
 * from the standart input.
 * 
 * The child process sends the input to the pipe, to the write end of it, and 
 * when the delimiter is encountered, it exits.
 * 
 * @param	pipex	pipex struct
 * @param	limiter	string that specifies the delimiter for the here_doc
*/
static void	process_here_doc(t_pipex *pipex, char *limiter)
{
	static char	*line;

	if (pipe(pipex->pipe) == -1)
		pipex_error(pipex, 0);
	pipex->pid = fork();
	if (pipex->pid == 0)
	{
		close(pipex->pipe[0]);
		ft_putstr_fd("> ", 1);
		line = get_next_line(0);
		while (line)
		{
			if (!ft_strncmp(line, limiter, ft_strlen(limiter))
				&& line[ft_strlen(limiter)] == '\n')
				exit(0);
			write(pipex->pipe[1], line, ft_strlen(line));
			ft_putstr_fd("> ", 1);
			line = get_next_line(0);
		}
	}
	else
		parent_process(pipex);
}

/**
 * @brief	This function processes the input arguments when the first argument
 * is "here_doc". It checks if the minimum required number of command-line
 * arguments are provided. If that's not the case, no_valid_argument() function
 * is called. Otherwise, it sets up the here_doc" processing using 
 * process_here_doc() function.
 * 
 * The outfile is opened for writing (O_WRONLY) and the ouput will be append
 * to the end of it (O_APPEND). If the outfile doesn't exists, it's created
 * (O_CREAT). It'll also be automatically closed when a new program is executed
 * using execve (__O_CLOEXEC). The file permissions are set to read, write, and 
 * execute for the owner, and no permissions for others (0777).
 * 
 * @param	pipex	pipex struct
 * @param	argc
 * @param	argv
 * 
*/
static void	process_input_here_doc(t_pipex *pipex, int argc, char **argv)
{
	if (argc < 6)
		no_valid_argument();
	else
		process_here_doc(pipex, argv[2]);
}

/**
 * @brief	This function proceses the input arguments when the first argument
 * is not "here_doc".
 * 
 * The infile is opened in read-only setup (O_RDONLY) and will be automatically
 * closed when a new program is executed using execve (__O_CLOEXEC). The file
 * permissions are set to read, write, and execute for the owner, and no 
 * permissions for others (0777).
 * 
 * The file descriptor of the infile (pipex->infile) is duplicated into 
 * the standard input file descriptor (STDIN_FILENO). This connects the standard 
 * input of the child process to the infile, allowing it to read from the file.
 * 
 * Then the file descriptor for the read end of the pipe is closed since it's
 * not used.
 * 
 * @param	pipex	pipex struct
 * @param	argc
 * @param	argv
*/
static void	process_input_basic(t_pipex *pipex, char **argv)
{
	if (pipe(pipex->pipe) == -1)
		pipex_error(pipex, 0);
	pipex->infile = open(argv[1], O_RDONLY | __O_CLOEXEC, 0777);
	if (pipex->infile == -1)
	{
		pipex_error(pipex, 1);
		return ;
	}
	dup2(pipex->infile, STDIN_FILENO);
	close(pipex->pipe[0]);
}

/**
 * @brief	This function parses the command-line arguments and environment
 * variables to initialize data needed for the program execution. It calls
 * helper functions (process_input_here doc or process_input_basis) based
 * on whether or not the first arugment is "here_doc".
 * 
 * The outfile is opened for writing (O_WRONLY) and truncated to a length
 * of 0 (O_TRUNC). If the outfile doesn't exist, it's created (O_CREAT). 
 * It'll also be automatically closed when a new program is executed using 
 * execve (__O_CLOEXEC). The file permissions are set to read, write, and 
 * execute for the owner, and no permissions for others (0777).
 * 
 * @param	pipex	pipex struct
 * @param	argv
 * @param	env		environment (global) variables that can be accessed by 
 * 					a program to obtain information about system's environment,
 * 					user, and configuration
*/
int	process_input(t_pipex *pipex, int argc, char **argv, char *env[])
{
	int	offset;

	pipex->argv = argv;
	pipex->argc = argc;
	if (!ft_strncmp(argv[1], "here_doc", 8))
		pipex->here_doc = 1;
	else
		pipex->here_doc = 0;
	pipex->env_path = get_path(env);
	pipex->paths = ft_split(pipex->env_path, ':');
	pipex->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC
			| __O_CLOEXEC, 0664);
	if (pipex->outfile == -1)
		pipex_error(pipex, 2);
	if (pipex->here_doc == 1)
	{
		process_input_here_doc(pipex, argc, argv);
		offset = 3;
	}
	else
	{
		process_input_basic(pipex, argv);
		offset = 2;
	}
	return (offset);
}
