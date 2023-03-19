/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares <psoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 00:02:29 by psoares           #+#    #+#             */
/*   Updated: 2022/03/08 00:02:30 by psoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	command_change(void)
{
	signal(SIGINT, command_sig);
	signal(SIGQUIT, command_sig);
}

void	main_change(void)
{
	signal(SIGINT, main_sig);
	signal(SIGQUIT, SIG_IGN);
}

void	heredoc_change(void)
{
	signal(SIGINT, heredoc_sig);
	signal(SIGQUIT, SIG_IGN);
}

void	quit_hand(int sig)
{
	printf("Quit: 3\n");
	g_error = 131;
}
