/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ancien.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaltun <aaltun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 13:36:24 by aaltun            #+#    #+#             */
/*   Updated: 2020/12/04 16:37:46 by aaltun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

    if (fd < 0 || !line || BUFFER_SIZE <= 0 || read(fd, buf, 0) < 0)
    {
        return (-1);
    }
    *line = ft_strdup("");
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
    if (statiq != NULL)
    {
        *line = ft_strdup(statiq);
        free(statiq);
        statiq = NULL;
    }
    return (0);
}

/*char *ft_loop(char *buf, int rd_ret, char *statiq, char **line)
{
    char *tmp;
    buf[rd_ret] = '\0';
    tmp = ft_strjoin(statiq, buf);
    free (statiq);
    while ()
    {
        if (find_backslash(tmp) >= 0)
        {
            statiq = ft_strdup(str_has_n(line, tmp));
            return (statiq);
        }
        else
        {
            statiq = ft_strdup(tmp);
            free(tmp);
        }
    }
    return ();
}*/

/*int main()
{
    int fd;
    char *line;

    fd = open("test.txt", O_RDONLY);
    while (get_next_line(fd, &line) > 0)
    {
        printf("get next line : %s-\n", line);
        free(line);
        //getchar(); //permet avoir une pause dans l'execution
    }
    printf("get next line : %s-\n", line);
    return (0);
}
*/