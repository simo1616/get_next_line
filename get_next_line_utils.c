/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 19:20:43 by mbendidi          #+#    #+#             */
/*   Updated: 2024/10/17 13:52:26 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	init_output(char **out)
{
	*out = (char *)malloc(sizeof(char) * 1);
	if (!*out)
		return (0);
	(*out)[0] = '\0';
	return (1);
}

ssize_t	find_char(char *buf, ssize_t x)
{
	while (buf[x])
	{
		if (buf[x] == '\n')
			return (x + 1);
		x++;
	}
	return (0);
}

ssize_t	ft_strlen(const char *s)
{
	ssize_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}
