/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares <psoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 23:07:28 by psoares           #+#    #+#             */
/*   Updated: 2022/03/07 23:07:29 by psoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	first_part(char **res, char *str, int start, int *i)
{
	while (start--)
	{
		(*res)[*i] = str[*i];
		(*i)++;
	}
}

void	second_part(char **res, char *d_val, int dollar_len, int *i)
{
	int	k;

	k = 0;
	while (dollar_len--)
	{
		(*res)[*i] = d_val[k];
		k++;
		(*i)++;
	}
}

void	third_part(char **res, char *str, int end, int *i)
{
	int	size_str;

	size_str = ft_strlen(str);
	while (end < size_str)
	{
		(*res)[*i] = str[end];
		end++;
		(*i)++;
	}
	(*res)[*i] = '\0';
}
