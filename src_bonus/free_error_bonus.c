/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 03:17:18 by aulicna           #+#    #+#             */
/*   Updated: 2023/12/15 17:09:32 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex_bonus.h"

/**
 * @brief	This funtion prints an error message and returns and error code (1)
 * when an error is encountered. It uses the perror() function that produces
 * a message on standard error describing the last error encountered (the value
 * of errno).
*/

int	pipex_error(void)
{
	perror("Encoutered error: ");
	return (1);
}

/**
 * @brief	This function frees a dynamically allocated array of strings.
 * 
 * @param	arr	the array of strings to free
*/

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr[i]);
	free(arr);
}

/**
 * @brief	This function displays an error message when a command is not found.
 * It frees allocated memory and exits the program with an error code.
 * 
 * @param	cmd		command that the program attempted to execute
 * @param	pipex	pipex struct
*/

void	command_not_found(char **cmd, t_pipex *pipex)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd(": command not found", 2);
	ft_putstr_fd("\n", 2);
	free_array(pipex->paths);
	free_array(pipex->cmd);
	exit(127);
}

/**
	* @brief	This function print an error message and usage instructions
	when a wrong number of command-line arguments is received.
*/

void	no_valid_argument(void)
{
	ft_putstr_fd("Input error: Wrong number of arguments received.\n\n", 2);
	ft_putstr_fd("Correct usage:\n", 2);
	ft_putstr_fd("./pipex_bonus infile cmd1 cmd2 cmd3 ... cmdn outfile\n", 2);
	ft_putstr_fd("./pipex_bonus here_doc LIMITER cmd cmd1 outfile\n", 2);
//	ft_printf("Input error: Wrong number of arguments received.\n\n");
//	ft_printf("Correct usage:\n");
//	ft_printf("./pipex_bonus infile cmd1 cmd2 cmd3 ... cmdn outfile\n");
//	ft_printf("./pipex_bonus here_doc LIMITER cmd cmd1 outfile\n");
	exit(0);
}
