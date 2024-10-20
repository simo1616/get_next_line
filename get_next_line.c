/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 19:20:48 by mbendidi          #+#    #+#             */
/*   Updated: 2024/10/19 12:13:08 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*str_add(char *a, char *b, ssize_t x, ssize_t y)
{
	ssize_t	i;
	char	*tmp;

	tmp = (char *)malloc(sizeof(char) * (ft_strlen(a) + y + 1));
	if (!tmp)
	{
		free(a);
		return (NULL);
	}
	i = 0;
	while (a[i])
	{
		tmp[i] = a[i];
		i++;
	}
	free(a);
	tmp[i + y] = '\0';
	while (y)
	{
		y--;
		tmp[i + y] = b[x + y];
	}
	return (tmp);
}

static int	read_file(int fd, char **out, char *buf)
{
	ssize_t	ret;

	ret = read(fd, buf, BUFFER_SIZE);
	if (ret == 0 && (**out))
		return (0);
	if (ret <= 0)
	{
		free(*out);
		*out = NULL;
		return (0);
	}
	buf[ret] = '\0';
	return (1);
}

static char	*extract_line(char *out, char *buf, ssize_t *pos, ssize_t *len)
{
	out = str_add(out, buf, *pos, *len);
	*pos += *len;
	*len = 0;
	return (out);
}

static int	buffer_append(char **out, char *buf, ssize_t *pos, ssize_t *len)
{
	*out = str_add(*out, buf, *pos, BUFFER_SIZE - *pos);
	if (!*out)
		return (0);
	*pos = 0;
	*len = 0;
	return (1);
}

char	*get_next_line(int fd)
{
	char			*out;
	static char		buf[BUFFER_SIZE + 1];
	static ssize_t	pos = 0;
	static ssize_t	len = 0;

	if (fd < 0 || BUFFER_SIZE < 1 || !init_output(&out))
		return (NULL);
	while (!len)
	{
		if (!pos && !read_file(fd, &out, buf))
			return (out);
		len = find_char(buf, pos) - pos;
		if (len > 0)
			return (extract_line(out, buf, &pos, &len));
		else if (!buffer_append(&out, buf, &pos, &len))
			return (NULL);
	}
	return (NULL);
}
