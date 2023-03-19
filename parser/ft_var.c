/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_var.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares <psoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 23:07:52 by psoares           #+#    #+#             */
/*   Updated: 2022/03/07 23:07:53 by psoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_var	*create_var(char *str, char *key, char *val)
{
	t_var	*newvar;

	newvar = malloc(sizeof(t_var));
	if (!newvar)
		return (NULL);
	newvar->str = str;
	newvar->v_key = key;
	newvar->v_val = val;
	newvar->next = NULL;
	return (newvar);
}

void	add_var(t_command *cmd, t_var *newel)
{
	t_var	*var;

	var = cmd->info->var;
	if (!newel)
		return ;
	if (!(var))
	{
		cmd->info->var = newel;
		return ;
	}
	while (var->next)
		var = var->next;
	var->next = newel;
}

int	change_var(t_command *cmd, char *key, char *value)
{
	t_var	*var;

	cmd->info->var = NULL;
	var = cmd->info->var;
	while (var)
	{
		if (!ft_strcmp(var->v_key, key))
		{
			var->v_val = value;
			return (1);
		}
		var = var->next;
	}
	return (0);
}

int	in_var(t_var *head, char *key)
{
	t_var	*var;

	var = head;
	while (var)
	{
		if (!ft_strcmp(var->v_key, key))
			return (1);
		var = var->next;
	}
	return (0);
}

int	delete_var(t_var **head, char *key)
{
	t_var	*var;
	t_var	*last;

	var = *head;
	last = NULL;
	while (var)
	{
		if (!ft_strcmp(var->v_key, key))
		{
			if (var->v_val)
				free(var->v_val);
			if (var->v_key)
				free(var->v_key);
			if (!last)
				*head = var->next;
			else
				last = var->next;
			return (1);
		}
		last = var;
		var = var->next;
	}
	return (0);
}
