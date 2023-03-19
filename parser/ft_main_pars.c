/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main_pars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares <psoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 23:07:37 by psoares           #+#    #+#             */
/*   Updated: 2022/03/07 23:07:38 by psoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	show(t_info *info);

int	parser(char *str, t_command *cmd)
{
	int	result;

	result = 1;
	while (*str)
	{
		while (*str == ' ')
			(str)++;
		redirect_search(&str, cmd);
		while (*str == ' ')
			(str)++;
		result = argument_search(&str, cmd);
		if (!result)
			return (0);
	}
	argument_edit(cmd);
	find_patterns(cmd);
	return (1);
}

int	argument_search(char **str, t_command *cmd)
{
	int	i;
	int	res;

	i = 0;
	res = 1;
	if (str && *str)
	{
		if (!argument_parser(*str, cmd, &i))
			return (0);
		if (cmd->flag_red)
		{
			cmd->flag_red = 0;
			res = redfile_add(cmd, *str, &i);
		}
		else if (**str)
			res = argument_add(cmd, *str, i);
		while (*str && i--)
			(*str)++;
	}
	if (res == 0)
		printf("memory error\n");
	return (res);
}

void	redirect_search(char **str, t_command *cmd)
{
	int	i;

	i = 0;
	if (str && *str && (**str == '>' || **str == '<'))
	{
		cmd->flag_red = 1;
		redirect_parser(str, cmd);
	}
}
