/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pattern_pars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellie <vellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 23:07:45 by psoares           #+#    #+#             */
/*   Updated: 2022/03/08 14:36:05 by vellie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_var_pattern(t_command *cmd, char *arg)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	key = NULL;
	value = NULL;
	if (!ft_first_sym(arg[i++]))
		return (0);
	while (ft_allowed_sym(arg[i]) && arg[i] != '=')
		i++;
	if (arg[i] != '=')
		return (0);
	if (!(arg[i]))
		value = NULL;
	else
		value = ft_substr(arg, i + 1, ft_strlen(arg));
	key = ft_substr((arg), 0, i);
	if (!change_var(cmd, key, value))
		add_var(cmd, create_var(arg, key, value));
	return (1);
}

int	file_pattern(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '/')
		i++;
	if (str[i] != '/')
		return (0);
	if (!access(str, 0) && str[ft_strlen(str) - 1] == '/')
		printf("minishell$: %s: is a directory\n", str);
	else if (!access(str, 0) && str[ft_strlen(str) - 1] != '/')
		printf("minishell$: %s: permission deny\n", str);
	else
		printf("minishell$: %s: No such file or directory\n", str);
	g_error = 1;
	return (1);
}

int	command_pattern(t_command *cmd, char *arg)
{
	cmd->cmd_name = arg;
	cmd->full_path = find_full_path(find_path(cmd->info->envp), arg);
	return (1);
}

int	find_patterns(t_command *cmd)
{
	int		i;
	char	**arg;

	i = 0;
	arg = cmd->argvstr;
	while (arg && (*arg))
	{
		if (env_var_pattern(cmd, *arg))
			(arg)++;
		else
		{	
			command_pattern(cmd, *arg);
			cmd->argvstr = arg;
			return (1);
		}
	}
	return (0);
}

int	check_comand(char *str, t_command *com)
{
	if (str && (!ft_strcmp(str, "echo") || !ft_strcmp(str, "cd")
			|| !ft_strcmp(str, "pwd") || !ft_strcmp(str, "export")
			|| !ft_strcmp(str, "unset") || !ft_strcmp(str, "env")
			|| !ft_strcmp(str, "exit") || !ft_strcmp(str, "bash")))
		return (0);
	else if (!access(com->full_path, 0))
		return (0);
	return (1);
}
