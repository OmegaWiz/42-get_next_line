/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:56:06 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/03/07 16:50:22 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*gnl_fnr(char **s1)
{
	if (*s1)
	{
		free(*s1);
		*s1 = NULL;
	}
	return (NULL);
}

char	*gnl_split(char **buf)
{
	char	*line;
	char	*tmp;
	char	*ptr;

	if (ft_strlen(*buf) == 0)
		return (gnl_fnr(buf));
	tmp = ft_strchr(*buf, 10);
	if (tmp == NULL)
	{
		line = *buf;
		*buf = 0;
		return (line);
	}
	line = *buf;
	ptr = *buf;
	if (line[tmp + 1 - ptr] != 0)
		*buf = ft_strdup(tmp + 1);
	else
		*buf = NULL;
	line[tmp + 1 - ptr] = 0;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buf[OPEN_MAX];
	char		*tmp;
	ssize_t		read_len;
	size_t		len;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (ft_strchr(buf[fd], '\n') == NULL)
	{
		len = ft_strlen(buf[fd]);
		tmp = buf[fd];
		buf[fd] = (char *) calloc(len + BUFFER_SIZE + 1, 1);
		if (!buf[fd])
			return (NULL);
		len = ft_strlcpy(buf[fd], tmp, len + 1);
		if (tmp != NULL)
			gnl_fnr(&tmp);
		read_len = read(fd, buf[fd] + len, BUFFER_SIZE);
		if (read_len < 0)
			return (gnl_fnr(&buf[fd]));
		if (read_len == 0)
			break;
		buf[fd][len + read_len] = 0;
	}
	return (gnl_split(&buf[fd]));
}
/*
int	gnl_lrsplit(char **buf, char **tmp_buf, char **tmp_read, ssize_t len)
{
	if (!*buf)
		return (0);
	if (len == 0)
		free(*tmp_read);
	len = 10;
	if (ft_strchr(*buf, len) == NULL)
	{
		*tmp_read = *buf;
		*buf = 0;
		return (1);
	}
	*tmp_buf = ft_substr(ft_strchr(*buf, len) + 1, 0, ft_strlen(*buf));
	if (!*tmp_buf && ft_strchr(*buf, len) - *buf != (long) ft_strlen(*buf) - 1)
		return (gnl_free_return(buf, NULL, NULL) != NULL);
	(*buf)[ft_strchr(*buf, len) + 1 - *buf] = 0;
	*tmp_read = *buf;
	*buf = *tmp_buf;
	*tmp_buf = 0;
	return (1);
}
*/
/*
char	*get_next_line(int fd)
{
	static char	*buf[OPEN_MAX];
	ssize_t		read_len;
	char		*tmp_buf;
	char		*tmp_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (ft_strchr(buf[fd], '\n') == NULL)
	{
		tmp_read = (char *) malloc(BUFFER_SIZE + 1);
		read_len = read(fd, tmp_read, BUFFER_SIZE);
		if (read_len < 0)
			return (gnl_free_return(&buf[fd], NULL, &tmp_read));
		tmp_read[read_len] = 0;
		if (read_len == 0)
			break ;
		tmp_buf = ft_strjoinfree(&buf[fd], &tmp_read);
		if (!tmp_buf)
			return (gnl_free_return(&buf[fd], NULL, &tmp_read));
		buf[fd] = tmp_buf;
		tmp_buf = 0;
	}
	if (!gnl_lrsplit(&buf[fd], &tmp_buf, &tmp_read, read_len))
		return (NULL);
	return (tmp_read);
}
*/
