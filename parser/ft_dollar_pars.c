/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar_pars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellie <vellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 23:07:26 by psoares           #+#    #+#             */
/*   Updated: 2022/03/08 14:36:05 by vellie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*return_err(char *dollar_key)
{
	char	*val;
	char	*val1;
	char	*ernum;

	val = NULL;
	val1 = NULL;
	val1 = ft_substr(dollar_key, 2, ft_strlen(dollar_key) - 2);
	ernum = ft_itoa(g_error / 256);
	val = ft_strjoin(ernum, val1);
	if (val1)
		free(val1);
	if (ernum)
		free(ernum);
	return (val);
}

static char	*return_value(t_command *cmd, char *str, int start, int end)
{
	char	*dollar_key;
	char	*dollar_val;

	dollar_key = NULL;
	dollar_key = ft_substr(str, start, end - start);
	if (dollar_key[1] == '?')
	{
		dollar_val = return_err(dollar_key);
	}
	else
		dollar_val = is_in_env(cmd->info, dollar_key);
	if (dollar_key)
		free(dollar_key);
	return (dollar_val);
}

char	*refactor_string(t_command *cmd, char *str, int start, int end)
{
	int		i;
	char	*res;
	char	*dollar_val;
	int		dollar_len;

	i = 0;
	dollar_val = NULL;
	dollar_val = return_value(cmd, str, start, end);
	if (!dollar_val)
		dollar_len = 0;
	else
		dollar_len = ft_strlen(dollar_val);
	if (dollar_len + start + ft_strlen(str) - end == 0)
		return (NULL);
	res = NULL;
	res = malloc(sizeof(char) * (dollar_len
				+ start + ft_strlen(str) - end + 1));
	if (!res)
		printf("oshybka pamyati\n");
	first_part(&res, str, start, &i);
	second_part(&res, dollar_val, dollar_len, &i);
	third_part(&res, str, end, &i);
	if (dollar_val)
		free(dollar_val);
	return (res);
}

int	dollar_parser(t_command *cmd, int num)
{
	int		i;
	int		end;
	int		start;
	char	*arg;
	char	*source;

	i = 0;
	arg = cmd->argvstr[num];
	start = 0;
	if (no_dollar(arg))
		return (0);
	end_start_dollar(arg, &start, &end);
	source = refactor_string(cmd, (arg), start, end);
	if (source)
	{
		if (cmd->argvstr[num])
			free(cmd->argvstr[num]);
		cmd->argvstr[num] = source;
		if (no_dollar(cmd->argvstr[num]))
			return (0);
		return (-1);
	}
	return (1);
}
