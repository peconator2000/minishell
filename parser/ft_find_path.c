/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellie <vellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 23:07:35 by psoares           #+#    #+#             */
/*   Updated: 2022/03/08 14:37:15 by vellie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_path_strcmp(char *s1, char *s2)
{
	size_t	i;
	size_t	sz;

	i = 0;
	sz = ft_strlen(s2);
	while (*s2 && *s1 == *s2)
	{
		s1++;
		s2++;
		i++;
	}
	if (i == sz)
		return (0);
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

char	*find_path(char **arg)
{
	char	**envp;

	envp = arg;
	while (envp && *envp)
	{
		if (!(ft_path_strcmp(*envp, "PATH=")))
			return (*envp);
		(envp)++;
	}
	return (NULL);
}

char	*free_all(char ***str, char *res)
{
	char	**start;

	start = *str;
	while (str && *str && **str)
	{
		free(**str);
		(*str)++;
	}
	if (start)
		free(start);
	return (res);
}

void	free_char(char **str)
{
	if (*str)
		free(*str);
	*str = NULL;
}

char	*find_full_path(char *env_path, char *command)
{
	char	**path_list;
	char	**start_path_list;
	char	*full_path;
	char	*newcmd;

	if (!env_path)
		return (NULL);
	path_list = ft_split(env_path, ':');
	full_path = NULL;
	newcmd = NULL;
	if (!access(command, 0))
	{
		printf("put do komandy\n");
		return (free_all(&path_list, ft_strdup(command)));
	}
	start_path_list = path_list;
	newcmd = ft_strjoin("/", command);
	while (*path_list)
	{
		full_path = ft_strjoin(*path_list, newcmd);
		if (!access(full_path, 0))
			break ;
		else if (full_path)
			free_char(&full_path);
		path_list++;
	}
	if (newcmd)
		free(newcmd);
	return (free_all(&start_path_list, full_path));
}
