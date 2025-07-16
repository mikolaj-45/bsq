/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurbane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:17:36 by emurbane          #+#    #+#             */
/*   Updated: 2025/07/16 23:09:21 by emurbane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_H
# define POINT_H

typedef struct point
{
	int	obs_y;
	int	visited;
}	t_point;

typedef struct rowinfo
{
	int		columns;
	char	*add_info;
	t_point	**map;
	int		lines;
}	t_rowinfo;
#endif
