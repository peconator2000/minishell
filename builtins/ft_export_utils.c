/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares <psoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 01:01:48 by psoares           #+#    #+#             */
/*   Updated: 2022/03/08 01:01:49 by psoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	var_parsing(t_command *cmd, char *arg, int *i)
{
	if (!ft_first_sym((arg)[(*i)++]))
		return (-1);
	while (ft_allowed_sym((arg)[*i]) && (arg)[*i] != '=')
		(*i)++;
	if ((arg)[*i] == '=')
		return (1);
	else if (!(arg[*i]))
		return (0);
	else
		return (-1);
}

void	add_to_envp(t_info *info, char *arg)
{
	int		i;
	int		size;
	char	**envp;
	char	**newenvp;

	i = 0;
	size = 0;
	newenvp = NULL;
	envp = info->envp;
	while (envp && envp[size])
		size++;
	newenvp = malloc(sizeof(char *) * (size + 2));
	while (i < size)
	{
		newenvp[i] = ft_strdup(envp[i]);
		i++;
	}
	newenvp[i] = ft_strdup(arg);
	newenvp[++i] = NULL;
	if (info->envp)
		free(info->envp);
	info->envp = newenvp;
}

void	move_var_type1(t_command *cmd, char *arg, int i)
{
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
	if (!((arg)[i]))
		value = NULL;
	else
		value = ft_substr(arg, i + 1, ft_strlen(arg));
	key = ft_substr((arg), 0, i);
	if (in_var(cmd->info->var, key))
		delete_var(&(cmd->info->var), key);
	if (in_env(cmd->info, key))
	{
		env_change(cmd->info, key, value);
		if (key)
			free(key);
	}
	else if (!env_paste(&(cmd->info->env), env_create(key, value), cmd->info))
		printf("memory error\n");
	add_to_envp(cmd->info, arg);
}

void	move_var_type2(t_command *cmd, char *arg, int i)
{
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
	key = ft_substr((arg), 0, i);
	if (in_var(cmd->info->var, key))
	{
		value = find_value(&(cmd->info->var), key);
		delete_var(&(cmd->info->var), key);
	}
	if (!in_env(cmd->info, key))
	{
		if (!env_paste(&(cmd->info->env), env_create(key, value), cmd->info))
			printf("memory error\n");
	}
}
