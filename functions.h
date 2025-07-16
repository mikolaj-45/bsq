/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurbane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:08:29 by emurbane          #+#    #+#             */
/*   Updated: 2025/07/16 23:10:05 by emurbane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H
# include "point.h"

extern int	g_size_x;
extern int	g_size_y;
extern char	g_empty;
extern char	g_obsticle;
extern char	g_full;

void	loops(t_point **tab);
void	give_value(t_point **tab, int index_x, int index_y, int x);
void	find_square(int index_x, int index_y, t_point **tab);
void	print_board(t_point **tab);
void	find_obs(t_point **t);
void	find_main(t_point **tab);
t_point	**readmap(char *filename);
void	print_map(t_point **map, int size_x, int size_y);
void	free_map(t_point **map, int lines);
int		ft_atoi(char *str);
int		is_valid(char *add_info, int *lines, int header_len);
int		fill_map(char *buffer, int pos, t_rowinfo info);
int		alloc_and_fill_row(t_point **row, char *buffer,
			int pos, t_rowinfo info);
int		count_columns(char *buffer, int pos);
int		open_file_and_allocate_buffer(char *filename, char **buffer);
int		read_and_expand(int fd, char **buffer);
#endif
