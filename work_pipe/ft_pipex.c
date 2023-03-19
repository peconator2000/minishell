/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellie <vellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 00:00:26 by psoares           #+#    #+#             */
/*   Updated: 2022/03/08 14:36:05 by vellie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	change_stdout(t_command *cmd)
{
	if (cmd->redout != STDOUT_FILENO)
	{
		dup2(cmd->redout, STDOUT_FILENO);
		close(cmd->redout);
		return (1);
	}
	return (0);
}

int	change_stdin(t_command *cmd)
{
	if (cmd->redin != STDIN_FILENO)
	{
		dup2(cmd->redin, STDIN_FILENO);
		close(cmd->redin);
		return (1);
	}
	return (0);
}

void	cmd_pipe_run(t_command *cmd)
{
	if (!change_stdout(cmd))
		dup2(cmd->fd[1], STDOUT_FILENO);
	change_stdin(cmd);
	close(cmd->fd[0]);
	close(cmd->fd[1]);
	if (!builtins(cmd))
	{
		if (!builtins(cmd))
		{
			if (!check_comand(cmd->cmd_name, cmd))
				execve(cmd->full_path, cmd->argvstr, cmd->info->envp);
			else if (!file_pattern(cmd->cmd_name))
				printf("minishell$: %s: command not found\n", cmd->cmd_name);
		}
	}
}

void	cmd_fd_change(t_command *cmd)
{
	dup2(cmd->fd[0], STDIN_FILENO);
	close(cmd->fd[1]);
	close(cmd->fd[0]);
}

int	pipes(t_command *cmd)
{
	pid_t	pid;

	if (pipe(cmd->fd))
		return (err("Can't create new pipe\n"));
	if (check_comand(cmd->cmd_name, cmd))
	{	
		if (!file_pattern(cmd->cmd_name))
			printf("minishell$: %s: command not found\n", cmd->cmd_name);
	}
	pid = fork();
	if (pid == 0)
		cmd_pipe_run(cmd);
	else if (pid > 0)
		cmd_fd_change(cmd);
	else
		return (err("Can't create new process\n"));
	return (1);
}
