/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaltun <aaltun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 15:09:13 by aaltun            #+#    #+#             */
/*   Updated: 2020/12/07 20:50:18 by aaltun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	find_backslash(char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int	str_has_n(char **line, char **str)
{
	int		remainder_len;
	char	*temp;

	*line = ft_substr(*str, 0, find_backslash(*str));
	remainder_len = ft_strlen(*str) - (find_backslash(*str) + 1);
	temp = ft_substr(*str, find_backslash(*str) + 1, remainder_len);
	free(*str);
	*str = ft_strdup(temp);
	free(temp);
	return (1);
}

int	tmp_has_n(char **line, char **statiq, char **tmp)
{
	int	remainder_len;

	*line = ft_substr(*tmp, 0, find_backslash(*tmp));
	remainder_len = ft_strlen(*tmp) - (find_backslash(*tmp) + 1);
	*statiq = ft_substr(*tmp, find_backslash(*tmp) + 1, remainder_len);
	free(*tmp);
	return (1);
}

int	ft_read(int rd_ret, char *buf, char **statiq, char **line)
{
	char	*tmp;

	buf[rd_ret] = '\0';
	tmp = ft_strjoin(*statiq, buf);
	free(*statiq);
	if (find_backslash(tmp) >= 0)
	{
		return (tmp_has_n(line, statiq, &tmp));
	}
	else
	{
		*statiq = ft_strdup(tmp);
		free(tmp);
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	*statiq = NULL;
	char		buf[BUFFER_SIZE + 1];
	int			rd_ret;

	if (fd < 0 || !line || BUFFER_SIZE <= 0 || read(fd, buf, 0) < 0)
		return (-1);
	if (statiq != NULL && find_backslash(statiq) >= 0)
	{
		return (str_has_n(line, &statiq));
	}
	while ((rd_ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		if (ft_read(rd_ret, buf, &statiq, line) == 1)
			return (1);
	}
	if (statiq != NULL)
	{
		*line = ft_strdup(statiq);
		free(statiq);
		statiq = NULL;
		return (0);
	}
	*line = ft_strdup("");
	return (0);
}
