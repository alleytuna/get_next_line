
int main()
{
    int fd;
    char *line;

    fd = open("sans.txt", O_RDONLY);
    while (get_next_line(fd, &line) > 0)
    {
        printf("get next line : %s-\n", line);
        free(line);
        //getchar(); //permet avoir une pause dans l'execution
    }
    return (0);
}
