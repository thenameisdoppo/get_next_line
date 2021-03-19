static int	saveLine(char **s, char **line)
{
	int	len;
	char	*temp;

	len = 0;
	while ((*s)[len] != '\n' && (*s)[len] != '\n')
		len++;
	if ((*s)[len] == '\n')
	{
		*line = ft_substr(*s, 0, len);
		temp = ft_strdup(&((*s)[len + 1]));
		free(*s);
		*s = tmp;
		if ((*s)[0] == '\0')
			ft_strdel(s);
	}
	else
	{
		*line = ft_strdup(*s);
		ft_strdel(s);
	}
	return (1);
}

static int	output(char **s, char **line, int ret, int fd)
{
	if (ret < 0 )
		return (-1);
	else if (ret == 0 && s[fd] == NULL)
		return (0);
	else
		return (saveLine(&s[fd], line));
}

int	get_next_line(int fd, char **line)
{
	int		ret;
	static char	*s[FD_SIZE];
	char		buff[BUFF_SIZE + 1];
	char		*temp;

	if (fd < 0 || line == NULL)
		return (-1);
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0 )
	{
		buff[ret] = '\0';
		if (s[fd] == NULL)
			s[fd] = ft_strdup(buff);
		else
		{
			temp = ft_strjoin(s[fd], buff);
			free(s[fd]);
			s[fd] = tmp;
		}
		if (ft_strchr(s[fd], '\n'))
			break;
	}
	return (output(s, line, ret, fd));
}
