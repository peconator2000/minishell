/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares <psoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 00:58:59 by psoares           #+#    #+#             */
/*   Updated: 2022/03/08 00:59:00 by psoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	clear_builtin(t_command *cmd)
{
	int			size;
	t_command	*head;

	head = cmd;
	size = 0;
	while (head)
	{
		head = head->next;
		size++;
	}
	if (size == 1 && is_built(cmd->cmd_name))
		return (1);
	return (0);
}

void	do_clear_built(t_command *cmd)
{
	int	save1;
	int	save0;

	save1 = dup(1);
	save0 = dup(0);
	redirects(cmd);
	if (cmd->redout != STDOUT_FILENO)
	{
		dup2(cmd->redout, STDOUT_FILENO);
		close(cmd->redout);
	}
	if (cmd->redin != STDIN_FILENO)
	{
		dup2(cmd->redin, STDIN_FILENO);
		close(cmd->redin);
	}
	builtins(cmd);
	dup2(save1, 1);
	dup2(save0, 0);
	close(save1);
	close(save0);
}

int	is_built(char *str)
{
	if (str && (!ft_strcmp(str, "echo") || !ft_strcmp(str, "cd")
			|| !ft_strcmp(str, "pwd") || !ft_strcmp(str, "export")
			|| !ft_strcmp(str, "unset") || !ft_strcmp(str, "env")
			|| !ft_strcmp(str, "exit") || !ft_strcmp(str, "bash")))
		return (1);
	return (0);
}

int	builtins(t_command *com)
{
	char	*cmd;
	int		built;

	if (!(com) || !(com->cmd_name))
		return (0);
	cmd = com->cmd_name;
	built = 0;
	if (cmd && !ft_strcmp(cmd, "echo"))
		built = b_echo(com->info);
	else if (cmd && !ft_strcmp(cmd, "cd"))
		built = b_cd(com->info);
	else if (cmd && !ft_strcmp(cmd, "pwd"))
		built = b_pwd();
	else if (cmd && !ft_strcmp(cmd, "export"))
		built = b_export(com);
	else if (cmd && !ft_strcmp(cmd, "unset"))
		built = b_unset(com);
	else if (cmd && !ft_strcmp(cmd, "env"))
		built = print_env(com->info);
	else if (cmd && !ft_strcmp(cmd, "exit"))
		exit(0);
	return (built);
}
