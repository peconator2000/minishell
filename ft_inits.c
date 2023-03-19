/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inits.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares <psoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 23:56:17 by psoares           #+#    #+#             */
/*   Updated: 2022/03/07 23:56:18 by psoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	info_data(t_info *info)
{
	info->err = 0;
	info->size = 0;
	info->var = NULL;
	info->env = NULL;
	info->envp = NULL;
	info->exit = 0;
	info->commands = NULL;
}

int	info_initialization(int argc, char **argv, char **envp, t_info **info)
{
	*info = malloc(sizeof(t_info));
	if (!(*info))
		return (0);
	info_data(*info);
	return (1);
}

void	clear_red_data(t_command *cmd)
{
	t_red	*next;

	if (!cmd || !(cmd->red))
		return ;
	while (cmd->red)
	{
		if (cmd->red->file)
			free(cmd->red->file);
		if (cmd->red->un_tok)
			free(cmd->red->un_tok);
		next = cmd->red->next;
		if (cmd->red)
			free(cmd->red);
		cmd->red = next;
	}
}

void	clear_cmd_data(t_command *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	if (cmd->cmd_name)
	{
		free(cmd->cmd_name);
		cmd->cmd_name = NULL;
	}
	if (cmd->full_path)
	{
		free(cmd->full_path);
		cmd->full_path = NULL;
	}
}

void	info_reinit(t_info *info)
{
	int			i;
	t_command	*cmd;
	t_command	*next;

	cmd = info->commands;
	while (cmd)
	{
		clear_cmd_data(cmd);
		next = cmd->next;
		if (cmd)
			free(cmd);
		cmd = next;
	}
	info->commands = NULL;
}
