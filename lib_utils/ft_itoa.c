/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares <psoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 23:30:50 by psoares           #+#    #+#             */
/*   Updated: 2022/03/07 23:30:51 by psoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	func_len(int i)
{
	int	p;

	p = 0;
	if (i == 0)
		return (1);
	while (i != 0)
	{
		i /= 10;
		p++;
	}
	return (p);
}

static	char	*ft_putnbr1(int n, char *str, int masslen, int f)
{
	int	i;

	if (f == 1)
		str[0] = '-';
	i = 1;
	while (n != 0)
	{
		str[masslen - i] = n % 10 + '0';
		n /= 10;
		i++;
	}
	str[masslen] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		masslen;
	int		f;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == -0)
		return (ft_strdup("0"));
	f = 0;
	if (n < 0)
	{
		n *= -1;
		f = 1;
		masslen = func_len(n) + 1;
	}
	else
		masslen = func_len(n);
	str = malloc(sizeof(char) * masslen + 1);
	if (!str)
		return (NULL);
	return (ft_putnbr1(n, str, masslen, f));
}
