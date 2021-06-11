/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourage <lfourage@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 12:48:03 by lfourage          #+#    #+#             */
/*   Updated: 2021/05/31 17:38:49 by lfourage         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>

unsigned int	ft_strlen(const char *str);
int				ft_atoi(char *n);
int				ft_strcmp(char *s1, char *s2);
int				ft_is_digit(int c);
int				ft_is_number(char *str);
int				ft_putchar_fd(int c, int fd);
int				ft_putstr_fd(const char *str, int fd);
int				ft_atoi_secure(int *r, char *n);
int				*ft_sort(int *t, int size);
long			ft_atol(char *n);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t nmemb, size_t size);
char			*ft_strdup(const char *str);
char			*ft_strchr(const char *s, int c);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_substr(char const *s, unsigned int start, size_t len);

#endif
