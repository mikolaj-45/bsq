/* ************************************************************************** */
/*                                                                            */
/*                                                    :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurbane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:30:00 by emurbane          #+#    #+#             */
/*   Updated: 2025/07/16 21:38:18 by mfrackow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "functions.h"

int	open_file_and_allocate_buffer(char *filename, char **buffer)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	*buffer = malloc(1024);
	if (!*buffer)
	{
		close(fd);
		return (-1);
	}
	return (fd);
}

int	expand_buffer(char **buffer, int current_size, int len)
{
	char	*newbuf;
	int		i;

	newbuf = malloc(current_size * 2);
	if (!newbuf)
		return (-1);
	i = 0;
	while (i < len)
	{
		newbuf[i] = (*buffer)[i];
		i++;
	}
	free(*buffer);
	*buffer = newbuf;
	return (0);
}

int	read_and_expand(int fd, char **buffer)
{
	char	c;
	int		len;
	int		size;

	len = 0;
	size = 1024;
	while (read(fd, &c, 1) == 1)
	{
		if (len + 1 >= size)
		{
			if (expand_buffer(buffer, size, len) == -1)
				return (-1);
			size *= 2;
		}
		(*buffer)[len++] = c;
	}
	(*buffer)[len] = '\0';
	return (0);
}
