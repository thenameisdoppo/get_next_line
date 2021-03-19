#include "get_next_line.h"

int	read_buf(t_buffer *buffer, char **line)
{
	size_t	i;
	size_t	j;
	int	found;

	i = ft_strlen(*line);
	if (!resize(line, i))
		return(-1);
	found = 0;
	j = 0;
	while (buffer->buf[j])
	{
		(*line)[i++] = buffer->buf[j];
		if (buffer->buf[j++] == '\n')
		{
			--i;
			found = 1;
			break;
		}
	}
	(*line)[i] = 0;
	i = 0;
	while (buffer->buf[j])
		buffer->buf[i++] = buffer->buf[j++];
	buffer->buf[i] = 0;
	return (found);

int	get_next_line(int fd, char **line)
{
	static t_buffe	*head;
	t_buffer	*buffer;
	int		size;
	int		found;

	if (BUFFER_SIZE <= 0 || !line || (!head && !(head = bew_buffer(fd))) || !(buffer = find_buffer(head, fd)))
		return (-1);
	*line = 0;
	if ((found = read_buf(buffer, line)))
		return (found);
	while ((size = read(fd, buffer->buf, BUFFER_SIZE)> 0))
	{
		buffer->buf[size] = 0;
		if ((found = read_buf(buffer, line)))
			return (found);
	}
	remove_buffer(&head, fd);
	return (size);
}
