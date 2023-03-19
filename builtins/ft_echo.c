/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellie <vellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 01:00:32 by psoares           #+#    #+#             */
/*   Updated: 2022/03/08 14:36:05 by vellie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	echo_pr(int i, t_command *argv)
{
	if (i != argv->n_args - 1)
		printf("%s ", argv->argvstr[i]);
	else
		printf("%s", argv->argvstr[i]);
}

int	b_echo(t_info *pars)
{
	int			i;
	t_command	*argv;

	argv = pars->commands;
	i = 1;
	if (pars->commands->n_args > 1)
	{
		if (!ft_strcmp(argv->argvstr[1], "-n"))
		{
			argv->flag = 1;
			i++;
		}
		while (argv->argvstr[i])
		{
			echo_pr(i, argv);
			i++;
		}
		if (!argv->flag)
			printf("\n");
	}
	else
		printf("\n");
	g_error = 0;
	return (1);
}
