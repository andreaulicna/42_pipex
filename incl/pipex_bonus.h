/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 03:48:32 by aulicna           #+#    #+#             */
/*   Updated: 2023/12/25 15:34:40 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libftprintf/ft_printf.h"
# include <sys/types.h>
# include <sys/wait.h> // waitpit
# include <fcntl.h>
# include <stdio.h> // perror
# include <unistd.h> // pipe
# include <stdlib.h>

/**
	* cmd		one cmd input at a time
	* env_path	paths to command read as one string
	* paths		all the paths returned from ft_split(env_path)
*/
typedef struct s_pipex
{
	int		pipe[2];
	int		pid;
	int		infile;
	int		outfile;
	char	**cmd;
	char	*env_path;
	char	**paths;
	int		here_doc;
	char	**argv;
	char	argc;
}	t_pipex;

// main_bonus.c
void	parent_process(t_pipex *pipex);

// free_error_bonus.c
int		pipex_error(t_pipex *pipex, int code);
void	free_array(char **arr);
void	command_not_found(char **cmd, t_pipex *pipex);
void	no_valid_argument(void);

// process_input_bonus.c
int		process_input(t_pipex *pipex, int argc, char **argv, char *env[]);

// command_bonus.c
char	*get_path(char **env);
void	execute_command(t_pipex *pipex, char **cmd, char *env[]);

#endif