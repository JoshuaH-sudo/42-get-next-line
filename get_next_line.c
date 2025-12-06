/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoban <jhoban@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:28:44 by jhoban            #+#    #+#             */
/*   Updated: 2025/12/01 12:26:05 by jhoban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

char	*append_buffer(char *left_over, char *buffer)
{
	char	*tmp;

	tmp = ft_joinstr(left_over, buffer);
	cleanup(left_over);
	if (!tmp)
		return (NULL);
	return (tmp);
}

char	*read_buffer(int fd, char *left_over)
{
	ssize_t	nread;
	char	*buffer;

	if (!left_over)
		left_over = ft_substr("", 0, 0);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (cleanup(left_over));
	nread = 1;
	while (nread > 0)
	{
		nread = read(fd, buffer, BUFFER_SIZE);
		if (nread == -1)
			return (cleanup(left_over), cleanup(buffer));
		if (nread == 0)
			break ;
		buffer[nread] = '\0';
		left_over = append_buffer(left_over, buffer);
		if (!left_over)
			return (cleanup(buffer));
		if (ft_strchr(left_over, '\n'))
			break ;
	}
	cleanup(buffer);
	return (left_over);
}

char	*extract_line(char *buffer)
{
	char	*line;
	ssize_t	i;

	i = 0;
	if (!buffer || buffer[0] == '\0')
		return (NULL);
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	line = ft_substr(buffer, 0, i + 1);
	return (line);
}

char	*extract_remaining(char *buffer)
{
	char	*remaining;
	ssize_t	i;
	ssize_t	len;

	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0')
		return (cleanup(buffer));
	len = ft_strlen(buffer);
	remaining = ft_substr(buffer, i + 1, len - (i + 1));
	cleanup(buffer);
	return (remaining);
}

char	*get_next_line(int fd)
{
	static char	*left_over;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (cleanup(left_over));
	left_over = read_buffer(fd, left_over);
	if (!left_over)
		return (cleanup(left_over));
	line = extract_line(left_over);
	left_over = extract_remaining(left_over);
	return (line);
}
