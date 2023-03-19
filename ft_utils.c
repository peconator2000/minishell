/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellie <vellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 01:07:27 by vellie            #+#    #+#             */
/*   Updated: 2022/03/08 01:09:23 by vellie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_child(t_info *info)
{
	signal(SIGQUIT, do_exit);
	do_cmd(info);
	exit(g_error / 256);
}

void	do_mom(t_info *info, int fd)
{
	signal(SIGINT, perenos);
	signal(SIGQUIT, SIG_IGN);
	waitpid(fd, &g_error, 0);
	if (clear_builtin(info->commands))
		do_clear_built(info->commands);
}

void	command_process(t_info *info)
{
	int	fd;

	fd = fork();
	if (fd == 0)
		do_child(info);
	else
		do_mom(info, fd);
	info_reinit(info);
}
