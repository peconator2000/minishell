/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares <psoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 23:31:02 by psoares           #+#    #+#             */
/*   Updated: 2022/03/07 23:31:03 by psoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *destination, const void *source, size_t n)
{
	unsigned char	*o;
	unsigned char	*z;
	size_t			l;

	o = (unsigned char *) destination;
	z = (unsigned char *) source;
	l = 0;
	if (!destination && !source)
		return (NULL);
	while (l < n)
	{
		o[l] = z[l];
		l++;
	}
	return ((void *) destination);
}
