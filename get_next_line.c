/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 10:47:45 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/03/06 16:22:30 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	{
		str = ft_strdup(s2);
		free(s2);
		return (str);
	}
	if (s2 == NULL)
		return (ft_strdup(s1));
	if (s2 == NULL && s1 == NULL)
		return (NULL);
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
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

char	*gnl_free_return(char *s1, char *s2, char *s3)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	if (s3)
		free(s3);
	return (NULL);
}

int	gnl_lrsplit(char *buf, char *tmp_buf, char *tmp_read, ssize_t len)
{
	if (!buf)
		return (0);
	if (len > 0)
		len = 10;
	tmp_buf = ft_substr(ft_strchr(buf, len), 0, ft_strlen(buf));
	tmp_read = ft_substr(buf, 0, ft_strchr(buf, len) - buf + 1);
	if (!tmp_buf || !tmp_read)
		return (0);
	free(buf);
	buf = ft_strdup(tmp_buf);
	if (!buf)
		return (0);
	free(tmp_buf);
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
		read_len = read(fd, tmp_read, BUFFER_SIZE);
		if (read_len < 0)
			return (gnl_free_return(buf[fd], tmp_buf, tmp_read));
		if (read_len == 0)
			break ;
		tmp_buf = ft_strjoinfree(buf[fd], tmp_read);
		if (!tmp_buf)
			return (gnl_free_return(buf[fd], tmp_buf, tmp_read));
		buf[fd] = tmp_buf;
		tmp_buf = 0;
	}
	if (!gnl_lrsplit(buf[fd], tmp_buf, tmp_read, read_len))
		return (gnl_free_return(buf[fd], tmp_buf, tmp_read));
	return (tmp_read);
}
