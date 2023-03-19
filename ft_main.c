/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellie <vellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 23:57:38 by psoares           #+#    #+#             */
/*   Updated: 2022/03/08 01:03:49 by vellie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_strs(char ***str)
{
	int		d;
	char	*tmp;

	d = 0;
	while (*str && (*str)[d])
	{
		tmp = (*str)[d];
		free(tmp);
		d++;
	}
	free(*str);
}

int	cmd_parser(char *str, t_info *info)
{
	int			i;
	char		**cmd_blocks;
	t_command	*head;
	t_command	*elem;

	i = -1;
	cmd_blocks = ft_split_pipe(str);
	elem = NULL;
	head = NULL;
	while (cmd_blocks && cmd_blocks[++i])
	{
		elem = ft_newcmd(info);
		if (!elem)
			printf("oshybka");
		if (!parser(cmd_blocks[i], elem))
		{
			free_strs(&cmd_blocks);
			return (0);
		}
		ft_lstadd_back(&head, elem);
		elem = NULL;
	}
	info->commands = head;
	free_strs(&cmd_blocks);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_info	*info;

	info = NULL;
	g_error = 0;
	info_initialization(argc, argv, envp, &info);
	envp_parser(info, envp);
	env_parser(info, envp);
	while (1)
	{
		main_change();
		str = readline("minishell$ ");
		if (str && !(*str))
			continue ;
		else if (!str)
			exit(0);
		add_history(str);
		if (!cmd_parser(str, info))
		{
			info_reinit(info);
			continue ;
		}
		command_process(info);
	}
}
