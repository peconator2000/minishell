/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argument_pars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellie <vellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 23:07:20 by psoares           #+#    #+#             */
/*   Updated: 2022/03/08 14:36:05 by vellie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redfile_add(t_command *cmd, char *str, int *i)
{
	t_red	*red;
	int		max;
	char	sym;

	max = 3;
	red = return_point(cmd->red);
	if (*i == 0)
	{
		if (!str[*i])
			red->un_tok = ft_substr("newline", 0, 7);
		else
		{
			sym = str[*i];
			while (str[*i] == sym && max--)
				(*i)++;
			red->un_tok = ft_substr(str, 0, *i);
		}
	}
	else
		red->file = ft_substr(str, 0, *i);
	if (!red->un_tok && !red->file)
		return (0);
	return (1);
}

int	argument_add(t_command *cmd, char *str, int i)
{
	char	**newargs;

	newargs = NULL;
	cmd->n_args += 1;
	newargs = allocate_memory(cmd);
	if (!newargs)
		return (0);
	if (cmd->argvstr)
	{
		free(cmd->argvstr);
		cmd->argvstr = NULL;
	}
	newargs[cmd->n_args - 1] = ft_substr(str, 0, i);
	if (!(newargs[cmd->n_args - 1]))
		printf("memory error\n");
	newargs[cmd->n_args] = NULL;
	cmd->argvstr = newargs;
	return (1);
}

int	pair_symbol(char *str, char sym, int *i)
{
	(*i)++;
	while (str && str[*i] != sym)
	{
		if (!str[*i])
		{
			printf("error of quotes\n");
			return (0);
		}
		(*i)++;
	}
	return (1);
}

int	argument_parser(char *str, t_command *cmd, int *y)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != ' ')
	{
		if (str[i] == '>' || str[i] == '<')
		{
			*y += i;
			return (1);
		}
		if (str[i] == '\'')
		{
			if (!pair_symbol(str, '\'', &i))
				return (0);
		}
		if (str[i] == '\"')
		{
			if (!pair_symbol(str, '\"', &i))
				return (0);
		}
		i++;
	}
	*y += i;
	return (1);
}
