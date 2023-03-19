/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares <psoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 23:36:01 by psoares           #+#    #+#             */
/*   Updated: 2022/03/07 23:36:02 by psoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *str)
{
	char	*dubl;
	int		i;

	dubl = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!dubl)
		return (NULL);
	i = 0;
	while (str[i])
	{
		dubl[i] = str[i];
		i++;
	}
	dubl[i] = '\0';
	return (dubl);
}
