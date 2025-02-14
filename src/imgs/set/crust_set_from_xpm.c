/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crust_set_from_xpm.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:00:58 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/13 12:25:42 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "img/set.h"

t_set	*crust_set_from_xpm(void *mlx, char *file_name, t_2d tile_size)
{
	t_set	*set;

	if (!mlx || !file_name || tile_size.x <= 0 || tile_size.y <= 0)
		return (NULL);
	set = malloc(sizeof(t_set));
	if (!set)
		return (NULL);
	ft_bzero(set, sizeof(t_set));
	set->mlx_ptr = mlx;
	set->img = crust_img_from_xpm(mlx, file_name);
	if (!set->img)
	{
		free(set);
		return (NULL);
	}
	set->tile_size = tile_size;
	return (set);
}
