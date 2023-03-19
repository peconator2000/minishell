/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellie <vellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 00:03:55 by psoares           #+#    #+#             */
/*   Updated: 2022/03/08 00:17:44 by vellie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	heredoc_move(char *phrase, int file_fd, char *str)
{
	heredoc_change();
	signal(SIGQUIT, SIG_IGN);
	str = readline("> ");
	while (ft_cmpstr(str, phrase))
	{
		if (!str)
			exit(0);
		if (write(file_fd, str, ft_strlen(str)) == -1)
			return (0);
		if (write(file_fd, "\n", 1) == -1)
			return (0);
		str = readline("> ");
	}
	exit(0);
}

static int	heredoc_run(t_red *red)
{
	int		file_fd;
	char	*str;
	char	*phrase;
	int		fd;

	phrase = red->file;
	str = NULL;
	file_fd = open("redirects/heredoc.txt", O_RDWR | O_TRUNC);
	if (file_fd == -1)
		return (0);
	fd = fork();
	if (fd == 0)
		heredoc_move(phrase, file_fd, str);
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		waitpid(fd, &g_error, 0);
	}
	close(file_fd);
	return (1);
}

static int	red_prehandler(t_red *red)
{
	t_red	*head;

	head = red;
	while (head)
	{
		if ((unexpected_token(head)))
			return (0);
		if (head->type == 4)
		{
			if (!heredoc_run(head))
				return (0);
		}
		head = head->next;
	}
	return (1);
}

int	redirects(t_command *cmd)
{
	t_red	*red;
	int		clean;

	red = cmd->red;
	if (!red)
		return (1);
	clean = 1;
	if (!red_prehandler(red))
		exit (0);
	while (red)
	{
		if (red->type == 1)
			clean = redirect_type1(red, cmd);
		else if (red->type == 2)
			clean = redirect_type2(red, cmd);
		else if (red->type == 3)
			clean = redirect_type3(red, cmd);
		else if (red->type == 4)
			clean = redirect_type4(cmd);
		if (!clean)
			exit(0);
		red = red->next;
	}
	return (1);
}
