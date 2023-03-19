/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellie <vellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 23:07:22 by psoares           #+#    #+#             */
/*   Updated: 2022/03/08 14:36:05 by vellie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	end_dollar(char *arg, int *end, int i)
{
	while (dollar_arg((arg)[i]))
		i++;
	*end = i;
}

void	end_start_dollar(char *arg, int *start, int *end)
{
	int	i;
	int	quotes1;
	int	quotes2;

	i = 0;
	quotes1 = 0;
	quotes2 = 0;
	*start = 0;
	while (arg[i])
	{
		if (arg[i] == '\'' && !quotes2)
			quotes1 = quotes1 ^ 1;
		else if (arg[i] == '\"' && !quotes1)
			quotes2 = quotes2 ^ 1;
		if (arg[i] == '$' && !quotes1)
		{
			if (!arg[i + 1] || arg[i + 1] == '\'' || arg[i + 1] == '\"')
			{
				i++;
				continue ;
			}
			(*start) = i;
			i++;
			break ;
		}
		i++;
	}
	end_dollar(arg, end, i);
}

int	dollar_arg(char sym)
{
	if (sym == '\'' || (sym == '\"'))
		return (0);
	else if (sym == ' ' || sym == '$' || sym == '\0')
		return (0);
	return (1);
}

int	no_dollar(char *arg)
{
	int	i;
	int	quotes1;
	int	quotes2;

	i = 0;
	quotes1 = 0;
	quotes2 = 0;
	while (arg[i])
	{
		if (arg[i] == '\'' && !quotes2)
			quotes1 = quotes1 ^ 1;
		else if (arg[i] == '\"' && !quotes1)
			quotes2 = quotes2 ^ 1;
		if (arg[i] == '$' && !quotes1)
		{
			if (arg[i + 1] == ' ' && quotes2)
			{
				i++;
				continue ;
			}
			if (arg[i + 1] && arg[i + 1] != '\'' && arg[i + 1] != '\"')
				return (0);
		}
		i++;
	}
	return (1);
}

void	showargs(t_command *cmd)
{
	int	i;

	i = 0;
	printf("\n-----------------------\nn_args = %d\n", cmd->n_args);
	while (cmd && cmd->argvstr && cmd->argvstr[i])
	{
		printf("arg[%d] = %s\n", i, cmd->argvstr[i]);
		i++;
	}
}
