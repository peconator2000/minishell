/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mega_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares <psoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 23:07:40 by psoares           #+#    #+#             */
/*   Updated: 2022/03/07 23:07:41 by psoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_first_sym(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	if (ch == '_')
		return (1);
	return (0);
}

int	ft_allowed_sym(int ch)
{
	if (ch >= '0' && ch <= '9')
		return (1);
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	if (ch == '_')
		return (1);
	return (0);
}

int	in_env(t_info *info, char *source)
{
	int		i;
	t_env	*env;

	env = info->env;
	while (source && env)
	{
		if (!ft_strcmp(env->key, source))
			return (1);
		env = env->next;
	}
	return (0);
}

int	env_change(t_info *info, char *key, char *new_val)
{
	t_env	*head;

	head = info->env;
	while (info->env)
	{
		if (!ft_strcmp(info->env->key, key))
		{
			if (info->env->value)
				free(info->env->value);
			info->env->value = new_val;
			info->env = head;
			return (1);
		}
		info->env = info->env->next;
	}
	info->env = head;
	return (0);
}

char	*find_value(t_var **head, char *key)
{
	t_var	*var;

	var = *head;
	while (var)
	{
		if (!ft_strcmp(var->v_key, key))
			return (ft_strdup(var->v_val));
		var = var->next;
	}
	return (NULL);
}
