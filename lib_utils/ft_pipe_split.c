/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellie <vellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 23:34:00 by psoares           #+#    #+#             */
/*   Updated: 2023/03/19 18:13:10 by vellie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	true_pipe(char sym, int one_br, int two_br)
{
	if (sym != '|')
		return (0);
	if (!one_br && !two_br)
		return (1);
	return (0);
}

static int	how_pipe_sym(const char *s)
{
	int	i;
	int	one_br;
	int	two_br;

	i = 0;
	one_br = 0;
	two_br = 0;
	while (*s && !true_pipe(*s, one_br, two_br))
	{
		if (*s == '\'')
			one_br = one_br ^ 1;
		else if (*s == '\"')
			two_br = two_br ^ 1;
		s++;
		i++;
	}
	return (i);
}

static int	how_pipe_string(const char *s)
{
	int	res;
	int	one_br;
	int	two_br;

	res = 0;
	one_br = 0;
	two_br = 0;
	while (*s)
	{
		if (*s && !true_pipe(*s, one_br, two_br))
		{
			if (*s == '\'')
				one_br = one_br ^ 1;
			else if (*s == '\"')
				two_br = two_br ^ 1;
			while (*s && !true_pipe(*s, one_br, two_br))
				s++;
			res++;
		}
		else
			s++;
	}
	return (res);
}

char	**ft_split_pipe(const char *s)
{
	size_t		i;
	int			k;
	int			strsz;
	char		**res;
	size_t		len;

	i = 0;
	k = 0;
	if (!s)
		return (0);
	res = NULL;
	res = malloc(sizeof(char *) * (how_pipe_string(s) + 1));
	if (!res)
		return (0);
	len = ft_strlen(s);
	while (i < len)
	{
		strsz = how_pipe_sym(&s[i]);
		if (strsz)
			res[k++] = ft_substr(s, i, strsz);
		i = i + strsz + 1;
	}
	res[k] = NULL;
	return (res);
}
