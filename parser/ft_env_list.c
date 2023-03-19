/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares <psoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 23:07:30 by psoares           #+#    #+#             */
/*   Updated: 2022/03/07 23:07:31 by psoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	datacheck(t_env **head, t_env *newel)
{
	if (!newel)
		return (0);
	if (!(*head))
	{
		*head = newel;
		(*head)->next = NULL;
		return (1);
	}
	return (0);
}

t_env	*env_last(t_env *env)
{
	while (env->next)
		env = env->next;
	return (env);
}

t_env	*env_create(char *key, char *value)
{
	t_env	*newel;

	newel = malloc(sizeof(t_env));
	if (!newel)
		return (NULL);
	newel->key = key;
	newel->value = value;
	newel->next = NULL;
	return (newel);
}

int	envcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		printf("TI OSHYBLAS\n");
	while (*(s1 + i) && *(s1 + i) == *(s2 + i))
		i++;
	if (*(s1 + i) == '\n')
		return (0);
	return (*((unsigned char *)s1 + i) - *((unsigned char *)s2 + i));
}

int	env_paste(t_env **head, t_env *newel, t_info *info)
{
	t_env	*start;
	t_env	*last;
	int		i;

	start = *head;
	last = NULL;
	i = 0;
	if (!newel || !start)
		return (datacheck(head, newel));
	while (start && (envcmp(start->key, newel->key) < 0))
	{
		last = start;
		start = start->next;
	}
	if (last == NULL)
	{
		newel->next = start;
		*head = newel;
		return (1);
	}
	last->next = newel;
	newel->next = start;
	return (1);
}
