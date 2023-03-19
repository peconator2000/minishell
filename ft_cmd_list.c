/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellie <vellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 23:55:26 by psoares           #+#    #+#             */
/*   Updated: 2022/03/08 14:36:05 by vellie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*ft_newcmd(t_info *info)
{
	t_command	*command;

	command = NULL;
	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->argvstr = NULL;
	command->cmd_name = NULL;
	command->full_path = NULL;
	command->flag = 0;
	command->fd_in = 0;
	command->fd_out = 1;
	command->n_args = 0;
	command->info = info;
	command->red = NULL;
	command->redin = 0;
	command->redout = 1;
	command->next = NULL;
	command->flag_red = 0;
	return (command);
}

int	ft_lstsize(t_command *head)
{
	int	res;

	res = 0;
	while (head)
	{
		res++;
		head = head->next;
	}
	return (res);
}

void	ft_lstadd_back(t_command **lst, t_command *newel)
{
	t_command	*mid;

	if (!newel)
		return ;
	if (!(*lst))
	{
		*lst = newel;
		(*lst)->info->commands = *lst;
		return ;
	}
	mid = *lst;
	while (mid->next)
		mid = mid->next;
	mid->next = newel;
}

void	ft_lstclear(t_command **lst)
{
	t_command	*mid;

	if (!(*lst))
		return ;
	while ((*lst))
	{
		mid = (*lst)->next;
		(*lst)->next = 0;
		if (*lst)
			free((*lst));
		*lst = mid;
	}
}
