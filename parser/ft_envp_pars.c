/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envp_pars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares <psoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 23:07:32 by psoares           #+#    #+#             */
/*   Updated: 2022/03/07 23:07:33 by psoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	envp_parser(t_info *info, char **envp)
{
	int		i;
	int		size;
	char	**newenvp;

	i = 0;
	size = 0;
	newenvp = NULL;
	while (envp && envp[size])
		size++;
	newenvp = malloc(sizeof(char *) * (size + 1));
	while (i < size)
	{
		newenvp[i] = ft_strdup(envp[i]);
		i++;
	}
	newenvp[i] = NULL;
	info->envp = newenvp;
}

int	env_parser(t_info *info, char **args)
{
	char	**envp;

	envp = args;
	while (envp && *envp)
	{
		if (!add_elem_env(info, *envp))
			return (0);
		(envp)++;
	}
	return (1);
}

int	add_elem_env(t_info *info, char *str)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!(str[i]))
		value = NULL;
	else
		value = ft_substr(str, i + 1, ft_strlen(str));
	key = ft_substr((str), 0, i);
	if (!env_paste(&(info->env), env_create(key, value), info))
		printf("memory error\n");
	return (1);
}

char	*is_in_env(t_info *info, char *source)
{
	int		i;
	t_env	*env;

	env = info->env;
	if (*source == '$')
		(source)++;
	while (source && env)
	{
		if (!ft_strcmp(env->key, source))
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}
