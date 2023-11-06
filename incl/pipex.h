/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:29:14 by aulicna           #+#    #+#             */
/*   Updated: 2023/11/06 23:40:59 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libftprintf/ft_printf.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h> // waitpit
# include <fcntl.h>
# include <stdio.h> // perror
# include <unistd.h> // pipe
# include <stdlib.h>

typedef	struct	s_pipex
{
	int	pipe[2];
	int	pid;
	int	infile;
	int	outfile;
	char	**cmd1; // input
	char	**cmd2; // input
	char	*env_path; // paths to command - read as one string
	char	**paths; // all the paths returned from ft_split(env_path) 

}	t_pipex;


#endif