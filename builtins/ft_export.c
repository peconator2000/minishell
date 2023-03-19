/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellie <vellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 01:01:07 by psoares           #+#    #+#             */
/*   Updated: 2022/03/08 14:36:05 by vellie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	export_with_args(t_command *cmd)
{
	int		type;
	int		j;
	int		i;
	char	**args;

	j = 1;
	args = cmd->argvstr;
	while (args && args[j])
	{
		i = 0;
		type = var_parsing(cmd, args[j], &i);
		if (type == 1)
			move_var_type1(cmd, args[j], i);
		else if (type == 0)
			move_var_type2(cmd, args[j], i);
		else
		{
			printf("bash: export: `%s': not a valid identifier\n", args[j]);
			return (0);
		}
		j++;
	}
	return (1);
}

static void	export_no_args(t_command *cmd)
{
	t_env	*env;

	env = cmd->info->env;
	while (env)
	{
		printf("declare -x %s", env->key);
		if (env->value)
			printf("=\"%s\"\n", env->value);
		else
			printf("\n");
		env = env->next;
	}
}

int	b_export(t_command *cmd)
{
	if (cmd->n_args == 1)
		export_no_args(cmd);
	else
		export_with_args(cmd);
	return (1);
}
