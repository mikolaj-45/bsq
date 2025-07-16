/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kochniak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:30:00 by kochniak          #+#    #+#             */
/*   Updated: 2025/07/13 14:57:19 by kochniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "number_to_words.h"

static void	process_dict_entry(char *buffer, int *i, t_dict_entry *dict,
		int *count)
{
	int		key_start;
	int		value_start;
	char	*key;
	char	*value;

	key_start = *i;
	while (buffer[*i] && buffer[*i] != ':')
		(*i)++;
	if (buffer[*i] != ':')
		return ;
	buffer[*i] = '\0';
	key = ft_strtrim(&buffer[key_start]);
	(*i)++;
	value_start = *i;
	while (buffer[*i] && buffer[*i] != '\n')
		(*i)++;
	buffer[*i] = '\0';
	value = ft_strtrim(&buffer[value_start]);
	if (key && value && *key && *value)
	{
		dict[*count].key = ft_strdup(key);
		dict[*count].value = ft_strdup(value);
		(*count)++;
	}
}

static int	read_file_to_buffer(char *filename, char *buffer)
{
	int	fd;
	int	bytes;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	bytes = read(fd, buffer, BUF_SIZE - 1);
	if (bytes < 0)
		return (-1);
	buffer[bytes] = '\0';
	close(fd);
	return (0);
}

static void	skip_whitespace(char *buffer, int *i)
{
	while (buffer[*i] && (buffer[*i] == ' ' || buffer[*i] == '\n'
			|| buffer[*i] == '\t'))
		(*i)++;
}

int	load_dict(t_dict_entry *dict, char *filename)
{
	char	buffer[BUF_SIZE];
	int		i;
	int		entry_count;

	if (read_file_to_buffer(filename, buffer) == -1)
		return (-1);
	i = 0;
	entry_count = 0;
	while (buffer[i] && entry_count < MAX_DICT_SIZE)
	{
		skip_whitespace(buffer, &i);
		if (!buffer[i])
			break ;
		process_dict_entry(buffer, &i, dict, &entry_count);
		i++;
	}
	return (entry_count);
}

void	print_dict(t_dict_entry *dict, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		write(1, "Key: ", 5);
		write(1, dict[i].key, ft_strlen(dict[i].key));
		write(1, ", Value: ", 9);
		write(1, dict[i].value, ft_strlen(dict[i].value));
		write(1, "\n", 1);
		i++;
	}
}
