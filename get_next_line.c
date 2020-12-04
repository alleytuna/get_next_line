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

char	*str_has_n(char **line, char *str)
{
	int remainder_len;
	char *temp;

    *line = ft_substr(str, 0, find_backslash(str));
    remainder_len = ft_strlen(str) - (find_backslash(str) + 1);
	temp = ft_substr(str, find_backslash(str) + 1, remainder_len);
	free(str);
	return (temp);
}

int ft_read(int rd_ret, char *buf, char **statiq, char **line)
{
    char * tmp;

    buf[rd_ret] = '\0';
    tmp = ft_strjoin(*statiq, buf);
    free (*statiq);
    if (find_backslash(tmp) >= 0)
    {
        *statiq = ft_strdup(str_has_n(line, tmp));
        return (1);
    }
    else
    {
        *statiq = ft_strdup(tmp);
        free(tmp);
    }
    return (0);
}

int get_next_line(int fd, char **line)
{
    static char *statiq = NULL;
    char buf[BUFFER_SIZE + 1];
    int rd_ret;

    if (fd < 0 || !line || BUFFER_SIZE <= 0 || read(fd, buf, 0) < 0)
        return (-1);
    *line = ft_strdup("");
    if (statiq != NULL && find_backslash(statiq) >= 0)
    {
        statiq = ft_strdup(str_has_n(line, statiq));
        return (1);
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
    }
    return (0);
}

int main()
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