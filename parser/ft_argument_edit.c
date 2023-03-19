/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argument_edit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellie <vellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 23:07:16 by psoares           #+#    #+#             */
/*   Updated: 2022/03/08 14:36:05 by vellie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	argument_edit(t_command *cmd)
{
	int		i;
	int		len;
	char	**arg;
	int		res;

	i = 0;
	arg = cmd->argvstr;
	while (cmd && cmd->argvstr && cmd->argvstr[i] && i < cmd->n_args)
	{
		res = dollar_parser(cmd, i);
		while (res == -1)
			res = dollar_parser(cmd, i);
		if (!res)
		{
			quotes_parser(cmd, i);
			i++;
		}
		else
		{
			delete_memory(cmd, i);
			(cmd->n_args)--;
		}
	}
	return (1);
}
