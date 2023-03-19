/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pars_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellie <vellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 23:07:42 by psoares           #+#    #+#             */
/*   Updated: 2022/03/08 14:36:05 by vellie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**allocate_memory(t_command *cmd)
{
	int		i;
	int		size;
	char	**res;

	i = 0;
	size = cmd->n_args;
	res = malloc(sizeof(char *) * (size + 1));
	if (!res)
		return (NULL);
	while (i < size - 1)
	{
		res[i] = cmd->argvstr[i];
		i++;
	}
	return (res);
}

int	delete_memory(t_command *cmd, int num)
{
	int		i;
	char	**res;
	char	**newargs;

	i = 0;
	if (!(cmd->n_args))
		return (0);
	res = malloc(sizeof(char *) * (cmd->n_args));
	if (!res)
		return (0);
	while (i < num)
	{
		res[i] = cmd->argvstr[i];
		i++;
	}
	while (i < cmd->n_args - 1)
	{
		res[i] = cmd->argvstr[i + 1];
		i++;
	}
	res[i] = NULL;
	if (cmd->argvstr)
		free(cmd->argvstr);
	cmd->argvstr = res;
	return (1);
}
