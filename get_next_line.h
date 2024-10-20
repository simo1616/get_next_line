/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 19:20:53 by mbendidi          #+#    #+#             */
/*   Updated: 2024/10/17 13:51:00 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 255
# endif

char	*get_next_line(int fd);
ssize_t	find_char(char *buf, ssize_t x);
ssize_t	ft_strlen(const char *s);
int		init_output(char **out);

#endif