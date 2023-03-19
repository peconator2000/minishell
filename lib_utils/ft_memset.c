/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares <psoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 23:31:18 by psoares           #+#    #+#             */
/*   Updated: 2022/03/07 23:31:19 by psoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *m, int s, size_t l)
{
	size_t			z;
	unsigned char	*o;

	o = (unsigned char *) m;
	z = 0;
	while (z <= l)
	{
		o[z] = s;
		z++;
	}
	return ((void *) m);
}
