/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares <psoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 23:36:18 by psoares           #+#    #+#             */
/*   Updated: 2022/03/07 23:36:19 by psoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	i;
	size_t	j;

	i = 0;
	j = start;
	if (!s)
		return (NULL);
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	dst = (char *)malloc(len + 1);
	if (!dst)
		return (NULL);
	if (start < ft_strlen(s))
	{
		while (i < len)
		{
			dst[i] = s[j];
			i++;
			j++;
		}
	}
	dst[i] = '\0';
	return (dst);
}
