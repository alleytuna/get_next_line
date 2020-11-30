/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaltun <aaltun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 15:35:54 by aaltun            #+#    #+#             */
/*   Updated: 2020/11/30 00:57:55 by aaltun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#define BUFFER_SIZE 1024

int find_backslash(char *str)
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

int get_next_line(int fd, char **line)
{
    static char *statiq;
    char *tmp;
    char buf[BUFFER_SIZE + 1];
    int remainder_len;
    int rd_ret;

    if (fd < 0 || fd > 256 || BUFFER_SIZE > 100000000 || BUFFER_SIZE <= 0)
    {
        *line = NULL;
        return (-1);
    }
    if (statiq != NULL && find_backslash(statiq) >= 0)
    {
        *line = ft_substr(statiq, 0, find_backslash(statiq));
        remainder_len = ft_strlen(statiq) - (find_backslash(statiq) + 1);
        tmp = ft_substr(statiq, find_backslash(statiq) + 1, remainder_len);
        free(statiq);
        statiq = ft_strdup(tmp);
        free(tmp);
        return (1);
    }
    while ((rd_ret = read(fd, buf, BUFFER_SIZE)) > 0)
    {
        buf[rd_ret] = '\0';
        tmp = ft_strjoin(statiq, buf);
        free (statiq);
        if (find_backslash(tmp) >= 0)
        {
            *line = ft_substr(tmp, 0, find_backslash(tmp));
            remainder_len = ft_strlen(tmp) - (find_backslash(tmp) + 1);
            statiq = ft_substr(tmp, find_backslash(tmp) + 1, remainder_len);
            free(tmp);
            return (1);
        }
        else
        {
            statiq = ft_strdup(tmp);
            free(tmp);
        }
    }
    *line = ft_strdup(statiq);
    return (0);
}

int main()
{
    int fd;
    char *line;

    fd = open("salut.txt", O_RDONLY);
    while (get_next_line(fd, &line) > 0)
    {
        printf("get next line : %s-\n", line);
        free(line);
        //getchar(); //permet avoir une pause dans l'execution
    }
    return (0);
}
