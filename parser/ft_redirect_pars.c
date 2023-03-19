/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_pars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares <psoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 23:07:49 by psoares           #+#    #+#             */
/*   Updated: 2022/03/07 23:07:50 by psoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_red	*return_point(t_red *red)
{
	while (red->next)
		red = red->next;
	return (red);
}

t_red	*create_red(void)
{
	t_red	*newel;

	newel = malloc(sizeof(t_red));
	if (!newel)
		return (NULL);
	newel->type = 0;
	newel->file = NULL;
	newel->next = NULL;
	newel->un_tok = NULL;
	return (newel);
}

int	red_add(t_red **head, t_red *newel, t_command *command)
{
	t_red	*start;

	start = *head;
	if (!newel)
		return (0);
	if (!(start))
	{
		*head = newel;
		(*head)->next = NULL;
		return (1);
	}
	while (start->next)
		start = start->next;
	start->next = newel;
	return (1);
}

int	return_redtype(char sym, int max)
{
	if (sym == '>' && max)
		return (1);
	else if (sym == '>')
		return (3);
	else if (sym == '<' && max)
		return (2);
	else
		return (4);
}

void	redirect_parser(char **str, t_command *cmd)
{
	int		max;
	char	sym;
	t_red	*red;

	if (!red_add(&(cmd->red), create_red(), cmd))
	{
		printf("oshibka");
		exit(0);
	}
	red = return_point(cmd->red);
	max = 2;
	sym = **str;
	while (**str == sym && max--)
		(*str)++;
	red->type = return_redtype(sym, max);
}
