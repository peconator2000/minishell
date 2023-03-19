/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares <psoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 01:00:02 by psoares           #+#    #+#             */
/*   Updated: 2022/03/08 01:00:16 by psoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_key(t_info info, char *str)
{
	t_env	*head1;
	char	*val;

	head1 = info.env;
	while (info.env)
	{
		if (!ft_strcmp(info.env->key, str))
		{
			val = info.env->value;
			info.env = head1;
			return (val);
		}
		info.env = info.env->next;
	}
	info.env = head1;
	return (NULL);
}

void	add_cd_env(t_info *info, char *home, char *pwd)
{
	int		i;
	char	*key_home;
	char	*key_pwd;
	char	*tmp;

	i = -1;
	key_home = ft_strjoin("PWD=", home);
	key_pwd = ft_strjoin("OLDPWD=", pwd);
	while (info->envp && info->envp[++i])
	{
		if (!ft_strncmp("OLDPWD=", info->envp[i], 7))
		{
			tmp = info->envp[i];
			info->envp[i] = key_pwd;
			free(tmp);
			tmp = NULL;
		}
		if (!ft_strncmp("PWD=", info->envp[i], 4))
		{
			tmp = info->envp[i];
			info->envp[i] = key_home;
			free(tmp);
			tmp = NULL;
		}
	}
}

void	change_dir(t_info *info, char *old_dir)
{
	char		*dir;
	t_env		*head1;

	dir = getcwd(NULL, 0);
	head1 = info->env;
	while (info->env)
	{
		if (!ft_strcmp("PWD", info->env->key))
		{
			if (info->env->value)
				free(info->env->value);
			info->env->value = dir;
		}
		else if (!ft_strcmp("OLDPWD", info->env->key))
			info->env->value = old_dir;
		info->env = info->env->next;
	}
	info->env = head1;
	add_cd_env(info, dir, old_dir);
}
