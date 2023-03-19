/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares <psoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 01:00:43 by psoares           #+#    #+#             */
/*   Updated: 2022/03/08 01:00:44 by psoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_env(t_info *pars)
{
	int	i;

	i = -1;
	while (pars->envp && pars->envp[++i])
		printf("%s\n", pars->envp[i]);
	g_error = 0;
	return (1);
}
