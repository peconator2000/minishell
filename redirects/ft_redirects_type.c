/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirects_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellie <vellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 00:03:20 by psoares           #+#    #+#             */
/*   Updated: 2022/03/11 16:52:31 by vellie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redirect_type1(t_red *red, t_command *cmd)//>
{
	int	file_fd;

	file_fd = open(red->file, O_CREAT, S_IRWXU | S_IRWXO | S_IRWXG);
	if (file_fd != -1)
		close(file_fd);
	file_fd = open(red->file, O_RDWR | O_TRUNC);
	if (file_fd == -1)
		return (0);
	cmd->redout = file_fd;
	return (1);
}

int	redirect_type2(t_red *red, t_command *cmd)//<
{
	int	file_fd;

	file_fd = open(red->file, O_RDWR | O_TRUNC);
	if (file_fd == -1)
	{
		printf("minishell: no such file or directory: %s\n", red->file);
		return (0);
	}
	cmd->redin = file_fd;
	return (1);
}

int	redirect_type3(t_red *red, t_command *cmd)//>>
{
	int	file_fd;

	file_fd = open(red->file, O_RDWR | O_APPEND);
	if (file_fd == -1)
	{
		printf("minishell: no such file or directory: %s\n", red->file);
		return (0);
	}
	cmd->redout = file_fd;
	return (1);
}

int	redirect_type4(t_command *cmd)//<<
{
	int	file_fd;

	file_fd = open("redirects/heredoc.txt", O_RDWR);
	if (!file_fd)
		return (0);
	cmd->redin = file_fd;
	return (1);
}
