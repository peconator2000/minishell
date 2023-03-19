/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes_pars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellie <vellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 23:07:47 by psoares           #+#    #+#             */
/*   Updated: 2022/03/08 14:36:05 by vellie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quotes_data(char sym, int quotes1, int quotes2, int first)
{
	if (quotes1 && first == '\'')
	{
		printf("quotes error\n");
		return (-1);
	}
	if (quotes2 && first == '\"')
	{
		printf("quotes error\n");
		return (-1);
	}
	return (sym);
}

int	end_start_quotes(char *arg, int *start, int *end)
{
	int	quotes1;
	int	quotes2;
	int	first;
	int	i;

	i = *start - 1;
	quotes1 = 0;
	quotes2 = 0;
	first = 0;
	while (arg && arg[++i])
	{
		if (arg[i] == '\'' && !quotes2)
		{
			if (first == 0)
				first = '\'';
			quotes1 = quotes1 ^ 1;
			if (!quotes1)
			{
				*end = i;
				return ('\'');
			}
			*start = i;
		}
		else if (arg[i] == '\"' && !quotes1)
		{
			if (first == 0)
				first = '\"';
			quotes2 = quotes2 ^ 1;
			if (!quotes2)
			{
				*end = i;
				return ('\"');
			}
			*start = i;
		}
	}
	return (quotes_data(arg[i], quotes1, quotes2, first));
}

int	refactor_quotes(t_command *cmd, int num, int start, int end)
{
	int		i;
	int		k;
	char	*res;
	char	*arg;

	i = 0;
	k = 0;
	arg = cmd->argvstr[num];
	res = malloc(sizeof(char) * (ft_strlen(arg) - 1));
	while (k < start)
	{
		res[i] = arg[k];
		i++;
		k++;
	}
	k++;
	while (k < end)
	{
		res[i] = arg[k];
		i++;
		k++;
	}
	k++;
	while (arg[k])
	{
		res[i] = arg[k];
		i++;
		k++;
	}
	res[i] = '\0';
	if (cmd->argvstr[num])
		free(cmd->argvstr[num]);
	cmd->argvstr[num] = res;
	return (1);
}

int	quotes_parser(t_command *cmd, int num)
{	
	int		i;
	int		start;
	int		end;
	int		res;
	char	*arg;

	i = 0;
	arg = cmd->argvstr[num];
	start = 0;
	end = ft_strlen(arg);
	res = end_start_quotes(arg, &start, &end);
	while (res != 0)
	{
		if (res == -1)
			exit(0);
		if (res == '\'' || res == '\"')
			refactor_quotes(cmd, num, start, end);
		arg = cmd->argvstr[num];
		start = end - 1;
		end = ft_strlen(arg);
		res = end_start_quotes(arg, &start, &end);
	}
	return (1);
}
