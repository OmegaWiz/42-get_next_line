/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 10:47:45 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/03/02 17:55:21 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <bits/posix1_lim.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>

size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);

char	*ft_strjoinfree(char *s1, char *s2)
{
	size_t	len;
	char	*str;
	size_t	i;

	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	if (s2 == NULL && s1 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = malloc(len);
	i = 0;
	if (str == NULL)
		return (str);
	while (i < len)
		str[i++] = 0;
	ft_strlcpy(str, s1, ft_strlen(s1) + 1);
	ft_strlcat(str, s2, ft_strlen(str) + ft_strlen(s2) + 1);
	free(s1);
	free(s2);
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	c %= 256;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == c)
		return ((char *)(s + i));
	return (NULL);
}

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
		read_len = read(fd, tmp_read, BUFFER_SIZE);
		if (read_len < 0 || (read_len == 0 && !tmp_read))
			return (NULL);
		tmp_buf = ft_strjoinfree(buf[fd], tmp_read);
		if (!tmp_buf)
			return (NULL);
		buf[fd] = tmp_buf;
		free(tmp_buf);
	}
	if (tmp_read == NULL)
		tmp_buf = ft_substr(ft_strchr(buf[fd], 10), 0, ft_strlen(buf[fd]));
	if (tmp_read == NULL)
		tmp_read = ft_substr(buf[fd], 0, ft_strchr(buf[fd], 10) - buf[fd] + 1);
	free(buf[fd]);
	buf[fd] = tmp_buf;
	return (tmp_read);
}

/*
size_t	gnl_findline(char *tmp, int is_endl)
{
	size_t	i;
	char	cmp;

	i = 0;
	if (is_endl)
		cmp = '\n';
	else
		cmp = '\0';
	if (!tmp)
		return (0);
	while (tmp[i])
	{
		if (tmp[i] == cmp)
			break ;
		i++;
	}
	return (i);
}

size_t	gnl_readbuf(int fd, char **tmp)
{
	ssize_t	len;
	char	*buf;
	char	*newtmp;

	buf = (char *) malloc(BUFFER_SIZE + 1);
	if (!buf)
		free(*tmp);
	if (!buf)
		return (SIZE_MAX);
	len = read(fd, buf, BUFFER_SIZE);
	if (len <= 0)
		buf = NULL;
	if (len <= 0)
		return (0);
	newtmp = ft_strjoin(*tmp, buf);
	free(*tmp);
	*tmp = newtmp;
	free(buf);
	if (!newtmp)
		return (SIZE_MAX);
	return (len);
}

char	*get_next_line(int fd)
{
	static char	*buf[OPEN_MAX];
	char		*tmp;
	char		*line;
	size_t		is_endl;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	is_endl = 1;
	tmp = ft_strdup(buf[fd]);
	while (gnl_findline(tmp, is_endl) == ft_strlen(tmp))
	{
		is_endl = gnl_readbuf(fd, &tmp);
		if (is_endl == SIZE_MAX)
			return (NULL);
		if (is_endl == 0)
			break ;
	}
	free(buf[fd]);
	buf[fd] = ft_substr(tmp, gnl_findline(tmp, is_endl) + 1, ft_strlen(tmp));
	line = ft_substr(tmp, 0, gnl_findline(tmp, is_endl) + 1);
	if (!buf[fd] || !line)
		return (NULL);
	if (tmp)
		free(tmp);
	return (line);
}
*/
