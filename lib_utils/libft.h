/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares <psoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 23:36:55 by psoares           #+#    #+#             */
/*   Updated: 2022/03/07 23:37:13 by psoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

char	**ft_split(const char *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(char *str);
int		ft_isalnum(int ch);
size_t	ft_strlen(const char *str);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split_pipe(const char *s);
void	*my_realloc2(char ***str, size_t size);
void	*ft_memset(void *m, int s, size_t l);
int		ft_intstr(char *str, int i);
void	*ft_memcpy(void *destination, const void *source, size_t n);
char	*ft_itoa(int n);

#endif
