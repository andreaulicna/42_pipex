/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 03:17:18 by aulicna           #+#    #+#             */
/*   Updated: 2023/12/25 15:17:22 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"

/**
 * @brief	This function prints an error message and returns and exits
 * the program with exit code (1) when an error is encountered. It uses
 * the perror() function that produces a message on standard error describing
 * the last error encountered (the value of errno).
 * 
 * @param	pipex	pipex struct that needs to be freed before exit
*/
int	pipex_error(t_pipex *pipex, int code)
{
	if (code == 1)
	{
		ft_putstr_fd("pipex: ", 2);
		perror(pipex->argv[1]);
	}
	else if (code == 2)
	{
		ft_putstr_fd("pipex: ", 2);
		perror(pipex->argv[4]);
	}
	else
		perror("pipex");
	ft_free(pipex);
	exit (1);
}

/**
 * @brief	This function frees a dynamically allocated array of strings.
 * 
 * @param	arr	the array of strings to free
*/
static void	free_array(char **arr)
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
 * @brief	This functions calls the free_array function on all dynamically
 * allocated arrays in the program.
 * 
 * @param	pipex	pipex struct
*/
void	ft_free(t_pipex *pipex)
{
	if (pipex->paths)
		free_array(pipex->paths);
	if (pipex->cmd1)
		free_array(pipex->cmd1);
	if (pipex->cmd2)
		free_array(pipex->cmd2);
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
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd(": command not found", 2);
	ft_putstr_fd("\n", 2);
	if (pipex->pid != 1)
	{
		ft_free(pipex);
		exit(127);
	}
}
