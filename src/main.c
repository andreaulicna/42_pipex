/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:27:46 by aulicna           #+#    #+#             */
/*   Updated: 2023/11/07 00:16:57 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"

int	pipex_error(void)
{
	perror("Encoutered error: ");
	return (1);
}

char	*get_command_full(char **paths, char *cmd)
{
	int	i;
	char	*cmd_full;
	char	*cmd_tmp;

	i = 0;
//	while (paths[i])
//	{
//		ft_putstr_fd(paths[i], 2);
//		ft_putstr_fd("\n", 2);
//		i++;
//	}
//	if (access(paths[0], 0) == 0)
//		return (paths[0]);
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

void	command_not_found(char **cmd)
{
	int	i;

	ft_printf("Command not found: %s\n", cmd[0]);
	i = 0;
	while(cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	exit(1);
}

void	execute_command(char **paths, char **cmd, char *env[])
{
	char	*cmd_full;
	
	cmd_full = get_command_full(paths, cmd[0]);
	if (execve(cmd_full, cmd, env) == -1)
		command_not_found(cmd);
}

void	child_process(t_pipex *pipex, char **argv, char *env[])
{
	pipex->infile = open(argv[1], O_RDONLY | __O_CLOEXEC, 0777);
	if (pipex->infile == -1)
		pipex_error();
	dup2(pipex->pipe[1], STDOUT_FILENO);
	close(pipex->pipe[1]);
	dup2(pipex->infile, STDIN_FILENO);
	close(pipex->pipe[0]);
	close(pipex->infile);
	execute_command(pipex->paths, pipex->cmd1, env);
}

void	parent_process(t_pipex *pipex, char **argv, char *env[])
{
	pipex->outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC | __O_CLOEXEC, 0777);
	if (pipex->outfile == -1)
		pipex_error();
	dup2(pipex->pipe[0], STDIN_FILENO);
	close(pipex->pipe[0]);
	dup2(pipex->outfile, STDOUT_FILENO);
	close(pipex->pipe[1]);
	close(pipex->outfile);
	execute_command(pipex->paths, pipex->cmd2, env);
}

int	pipex_handler(t_pipex *pipex, char **argv, char *env[])
{
	if(pipe(pipex->pipe) == -1)
		pipex_error();
	pipex->pid = fork();
	if (pipex->pid == -1)
		pipex_error();
	if (pipex->pid == 0)
		child_process(pipex, argv, env);
	waitpid(pipex->pid, NULL, 0);
	parent_process(pipex, argv, env);
	return (0);
}

char	*get_path(char **envp)
{
	int	i;

	i = 0;
	while (ft_strncmp("PATH=", envp[i], 5))
		i++;
	return (envp[i] + 5);
}


int	process_input(t_pipex *pipex, char **argv, char *env[])
{
	pipex->cmd1 = ft_split(argv[2], ' ');
	pipex->cmd2 = ft_split(argv[3], ' ');
	pipex->env_path = get_path(env);
	pipex->paths = ft_split(pipex->env_path, ':');
	return (0);
}

int	main(int argc, char **argv, char *env[])
{
	t_pipex	pipex;

	if (argc < 5)
	{
		ft_printf("Input error: Wrong number of arguments received.\n\n");
		ft_printf("Correct usage: ./pipex infile cmd1 cmd2 outfile\n");
	//	ft_printf("Correct usage:\n");
	//	ft_printf("./pipex_bonus infile cmd1 cmd2 cmd3 ... cmdn outfile\n");
	//	ft_printf("./pipex_bonus here_doc LIMITER cmd cmd1 outfile\n");
		exit(0);
	}
	process_input(&pipex, argv, env);
	pipex_handler(&pipex, argv, env);
	return (0);
}