/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellie <vellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 23:59:40 by psoares           #+#    #+#             */
/*   Updated: 2022/03/08 14:36:05 by vellie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	wait_process(t_command *cmd, int size)
{
	close(cmd->fd[0]);
	while (size)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, quit_hand);
		waitpid(-1, &g_error, 0);
		if (g_error == 3)
			g_error = 131 * 256;
		size--;
	}
}

void	do_cmd(t_info *info)
{
	t_command	*head;

	head = info->commands;
	if (clear_builtin(head))
		exit(0);
	while (head && head->next)
	{
		redirects(head);
		if (!pipes(head))
		{
			printf("pipe error!\n");
			exit(0);
		}
		head = head->next;
	}
	head->fd[0] = 0;
	if (head)
	{
		redirects(head);
		cmd_run(head);
	}
}

int	sizeofcmd(t_command *head)
{
	int	i;

	i = 0;
	while (head)
	{
		if (!is_built(head->cmd_name))
			i++;
		head = head->next;
	}
	return (i);
}

void	execute_cmd(t_command *cmd)
{
	if (!builtins(cmd))
	{
		if (!check_comand(cmd->cmd_name, cmd))
			execve(cmd->full_path, cmd->argvstr, cmd->info->envp);
		else if (!file_pattern(cmd->cmd_name))
		{
			printf("minishell$: %s: command not found\n", cmd->cmd_name);
			g_error = 127;
		}
	}
}

void	cmd_run(t_command *cmd)
{
	pid_t	pid;
	int		size;

	size = sizeofcmd(cmd->info->commands);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, command_sig);
		change_stdout(cmd);
		change_stdin(cmd);
		execute_cmd(cmd);
		exit(g_error);
	}
	else
		wait_process(cmd, size);
}
