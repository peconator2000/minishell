/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellie <vellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 01:02:35 by psoares           #+#    #+#             */
/*   Updated: 2022/03/08 14:36:05 by vellie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	return_ev(t_info *info, t_env *mid)
{
	if (info->env)
		free(info->env);
	info->env = mid;
	return (1);
}

int	delete_env_var(t_info *info, char *key)
{
	t_env	*last;
	t_env	*env;
	t_env	*mid;

	env = info->env;
	last = NULL;
	if (!env)
		return (0);
	while (info->env)
	{
		if (!ft_strcmp(info->env->key, key))
		{
			mid = info->env->next;
			if (!last)
				return (return_ev(info, mid));
			last->next = mid;
			return (return_ev(info, env));
		}
		last = info->env;
		info->env = info->env->next;
	}
	info->env = env;
	return (1);
}

void	unset_elem(t_command *cmd, char *arg)
{
	int		i;
	t_env	*env;

	i = 0;
	if (!ft_first_sym((arg)[(i)++]))
	{
		printf("bash: unset: `%s': not a valid identifier\n", arg);
		g_error = 1;
		return ;
	}
	while (ft_allowed_sym((arg)[i]))
		(i)++;
	if (i != ft_strlen(arg))
	{
		printf("bash: unset: `%s': not a valid identifier\n", arg);
		g_error = 1;
		return ;
	}
	delete_env_var(cmd->info, arg);
}

int	b_unset(t_command *cmd)
{
	int		i;
	char	**arg;

	i = 0;
	arg = cmd->argvstr;
	while (arg && arg[++i])
		unset_elem(cmd, arg[i]);
	return (1);
}
