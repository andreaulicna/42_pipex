/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:29:14 by aulicna           #+#    #+#             */
/*   Updated: 2023/11/07 03:34:46 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libftprintf/ft_printf.h"
# include <sys/types.h>
# include <sys/wait.h> // waitpit
# include <fcntl.h>
# include <stdio.h> // perror
# include <unistd.h> // pipe
# include <stdlib.h>

/**
	* cmd1					input 
	* cmd2 				input
	* env_path	paths to command read as one string
	*	paths				all the paths returned from ft_split(env_path)
*/

typedef struct s_pipex
{
	int		pipe[2];
	int		pid;
	int		infile;
	int		outfile;
	char	**cmd1;
	char	**cmd2;
	char	*env_path;
	char	**paths;
}	t_pipex;

// free_error.c
int		pipex_error(void);
void	ft_free(t_pipex *pipex);
void	command_not_found(char **cmd, t_pipex *pipex);

// command.c
char	*get_path(char **env);
void	execute_command(t_pipex *pipex, char **cmd, char *env[]);

#endif