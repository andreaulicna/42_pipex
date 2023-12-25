/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 01:29:13 by aulicna           #+#    #+#             */
/*   Updated: 2023/12/25 15:22:09 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"

/**
 * @brief	This function parses the command-line arguments and environment
 * variables to initialize data needed for the program execution.
 * 
 * The infile is opened in read-only setup (O_RDONLY) and will be automatically
 * closed when a new program is executed using execve (__O_CLOEXEC). The file
 * permissions are set to read, write, and execute for the owner, and no 
 * permissions for others (0777).
 * 
 * The outfile is opened for writing (O_WRONLY) and truncated to a lenght
 * of 0 (O_TRUNC). If the outfile doesn't exists, it's created (O_CREAT). 
 * It'll also be automatically closed when a new program is executed using 
 * execve (__O_CLOEXEC). The file permissions are set to read and write for
 * the owner and read-only for others
 * 
 * @param	pipex	pipex struct
 * @param	argv
 * @param	env		environment (global) variables that can be accessed by 
 * 					a program to obtain information about system's environment,
 * 					user, and configuration
*/
void	process_input(t_pipex *pipex, char **argv, char *env[])
{
	pipex->argv = argv;
	pipex->cmd1 = ft_split(argv[2], ' ');
	pipex->cmd2 = ft_split(argv[3], ' ');
	pipex->env_path = get_path(env);
	pipex->paths = ft_split(pipex->env_path, ':');
}
