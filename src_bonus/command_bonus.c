/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 03:16:20 by aulicna           #+#    #+#             */
/*   Updated: 2023/12/16 14:09:04 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex_bonus.h"

/**
 * @brief	This function extracts the PATH environment variable from the given 
 * environment variables and returns it.
 * 
 * @param	env		environment (global) variables that can be accessed by 
 * 					a program to obtain information about system's environment,
 * 					user, and configuration
*/

char	*get_path(char **env)
{
	int	i;

	i = 0;
	while (ft_strncmp("PATH=", env[i], 5))
		i++;
	return (env[i] + 5);
}

/**
 * @brief	This function  uses a list of directories (paths) and a command (cmd)
 * to constructs the full path to the command. It does so by searching for it in 
 * the specified directories. If the command is found, the full path is returned.
 * Otherwise, it returns NULL.
*/

static char	*get_command_full(char **paths, char *cmd)
{
	int		i;
	char	*cmd_full;
	char	*cmd_tmp;

	i = 0;
	while (paths[i])
	{
		cmd_tmp = ft_strjoin(paths[i], "/");
		cmd_full = ft_strjoin(cmd_tmp, cmd);
		free(cmd_tmp);
		if (access(cmd_full, 0) == 0)
			return (cmd_full);
		free(cmd_full);
		i++;
	}
	return (NULL);
}

/**
 * @brief	This function uses an array of paths, a command to execute, and 
 * the environment information and attempts to execute the command. If
 * the execution fails, it calls command_not_found function to handle the error.
 * 
 * @param	pipex	pipex struct
 * @param	cmd		command to execute
 * @param	env		environment (global) variables that can be accessed by 
 * 					a program to obtain information about system's environment,
 * 					user, and configuration
*/

void	execute_command(t_pipex *pipex, char **cmd, char *env[])
{
	char	*cmd_full;

	cmd_full = get_command_full(pipex->paths, cmd[0]);
	if (execve(cmd_full, cmd, env) == -1)
		command_not_found(cmd, pipex);
}
