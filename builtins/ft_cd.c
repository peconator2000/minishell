/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellie <vellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 00:59:35 by psoares           #+#    #+#             */
/*   Updated: 2022/03/08 14:36:05 by vellie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd_single(t_info *info)
{
	char	*home;
	char	*pwd;
	t_env	*head1;

	head1 = info->env;
	home = find_key(*info, "HOME");
	pwd = find_key(*info, "PWD");
	while (info->env)
	{
		if (!ft_strcmp("PWD", info->env->key))
			info->env->value = home;
		else if (!ft_strcmp("OLDPWD", info->env->key))
			info->env->value = pwd;
		info->env = info->env->next;
	}
	info->env = head1;
	add_cd_env(info, home, pwd);
}

void	cd_move(t_info *info)
{
	char		*old_dir;
	char		*new_dir;

	old_dir = getcwd(NULL, 0);
	new_dir = info->commands->argvstr[1];
	if (info->commands->argvstr[1][0] == '~')
		new_dir = ft_strjoin(find_key(*info, "HOME"), (new_dir + 1));
	if (chdir(new_dir))
	{
		printf("cd: no such file or directory: \n");
		g_error = 1;
	}
	else
		change_dir(info, old_dir);
	if (old_dir)
		free(old_dir);
	return ;
}

void	cd_home(t_info *info)
{
	char	*old_dir;

	if (chdir(find_key(*info, "HOME")))
	{
		printf("cd: no such file or directory: \n");
		g_error = 1;
	}
	else
		cd_single(info);
	return ;
}

int	b_cd(t_info *info)
{
	if (info->commands->n_args == 1)
		cd_home(info);
	else
		cd_move(info);
	return (1);
}
