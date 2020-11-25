/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaltun <aaltun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 09:37:38 by aaltun            #+#    #+#             */
/*   Updated: 2020/11/23 15:29:38 by aaltun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *str, int fd);
char	*ft_strchr(const char *str, int search);
int	    ft_strlen(const char *str);
char	*ft_substr(char const *str, unsigned int start, size_t len);
int     get_next_line(int fd, char **line);
char	*ft_strjoin(char const *s1, char const *s2);
char    *ft_strcpy(char *dest, char *src);
void	*ft_memset(void *ptr, int value, size_t len);
char	*ft_strdup(const char *src);

#endif