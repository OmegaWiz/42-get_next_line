/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:56:06 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/03/07 10:28:37 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoinfree(char **s1, char **s2)
{
	char	*str;
	size_t	i;

	if (!*s1)
	{
		str = ft_strdup(*s2);
		free(*s2);
		return (str);
	}
	if (!*s2)
		return (ft_strdup(*s1));
	if (!*s1 && !*s2)
		return (NULL);
	str = malloc(ft_strlen(*s1) + ft_strlen(*s2) + 1);
	i = 0;
	if (!str)
		return (str);
	while (i < ft_strlen(*s1) + ft_strlen(*s2) + 1)
		str[i++] = 0;
	ft_strlcpy(str, *s1, ft_strlen(*s1) + 1);
	ft_strlcat(str, *s2, ft_strlen(str) + ft_strlen(*s2) + 1);
	free(*s1);
	free(*s2);
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	c %= 256;
	i = 0;
	if (!s)
		return (NULL);
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

char	*gnl_free_return(char **s1, char **s2, char **s3)
{
	if (s1)
	{
		if (*s1)
			free(*s1);
	}
	if (s2)
	{
		if (*s2)
			free(*s2);
	}
	if (s3)
	{
		if (*s3)
			free(*s3);
	}
	return (NULL);
}

int	gnl_lrsplit(char **buf, char **tmp_buf, char **tmp_read, ssize_t len)
{
	if (!*buf)
		return (0);
	len = 10;
	if (ft_strchr(*buf, len) == NULL)
	{
		*tmp_read = *buf;
		*buf = 0;
		return (1);
	}
	*tmp_buf = ft_substr(ft_strchr(*buf, len) + 1, 0, ft_strlen(*buf));
	if (!*tmp_buf)
		return (gnl_free_return(buf, NULL, NULL) != NULL);
	*tmp_read = ft_substr(*buf, 0, ft_strchr(*buf, len) - *buf + 1);
	if (!*tmp_read)
		return (gnl_free_return(buf, tmp_buf, NULL) != NULL);
	*buf = *tmp_buf;
	*tmp_buf = 0;
	return (1);
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
		tmp_read = (char *) malloc(BUFFER_SIZE);
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
