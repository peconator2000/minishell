/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirects_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares <psoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 00:05:21 by psoares           #+#    #+#             */
/*   Updated: 2022/03/08 00:05:22 by psoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cmpstr(const char *s1, const char *s2)
{
	int	i;
	int	size_s1;
	int	size_s2;

	i = 0;
	if (!s1 || !s2)
		return (1);
	size_s2 = ft_strlen(s2);
	size_s1 = ft_strlen(s1);
	if (size_s1 != size_s2)
		return (1);
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
		i++;
	}
	if (i == size_s1)
		return (0);
	return (1);
}

int	unexpected_token(t_red *red)
{
	if (red->un_tok == NULL)
		return (0);
	printf("syntax error near unexpected token `%s'\n", red->un_tok);
	return (1);
}
