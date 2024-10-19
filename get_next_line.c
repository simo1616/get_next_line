/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 19:20:48 by mbendidi          #+#    #+#             */
/*   Updated: 2024/10/19 09:55:43 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*extract_line(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (!buffer || !*buffer)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = (char *)malloc(i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*update_buffer(char *buffer)
{
	int		i;
	char	*new_buffer;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	i++;
	new_buffer = ft_strdup(buffer + i);
	if (!new_buffer)
	{
		free(buffer);
		return (NULL);
	}
	free(buffer);
	return (new_buffer);
}

static int	read_and_join(int fd, char **buffer, char *temp_buffer)
{
	ssize_t	bytes_read;
	char	*tmp;

	bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
	if (bytes_read == -1)
		return (-1);
	if (bytes_read == 0)
		return (0);
	temp_buffer[bytes_read] = '\0';
	tmp = *buffer;
	*buffer = ft_strjoin(*buffer, temp_buffer);
	if (!*buffer)
	{
		free(tmp);
		return (-1);
	}
	free(tmp);
	return (1);
}

static char	*read_file(int fd, char *buffer)
{
	char	*temp_buffer;
	int		ret;

	temp_buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!temp_buffer)
		return (NULL);
	ret = 1;
	while (!ft_strchr(buffer, '\n') && ret != 0)
	{
		ret = read_and_join(fd, &buffer, temp_buffer);
		if (ret == -1)
		{
			free(temp_buffer);
			return (NULL);
		}
		temp_buffer[ret] = '\0';
		if (ret == 0)
			break ;
	}
	free(temp_buffer);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	line = extract_line(buffer);
	buffer = update_buffer(buffer);
	if (!line && buffer)
	{
		free(buffer);
		buffer = NULL;
	}
	return (line);
}
