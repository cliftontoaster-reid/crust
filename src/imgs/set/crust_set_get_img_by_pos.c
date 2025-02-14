/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crust_set_get_img_by_pos.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 11:43:22 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/14 11:43:23 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "img/set.h"

t_img	*crust_set_get_img_by_pos(t_set *set, t_2d pos)
{
	t_img	*img;
	t_2d	tile_pos;
	int		max_tile_x;
	int		max_tile_y;

	if (!set || !set->img || pos.x < 0 || pos.y < 0)
		return (NULL);
	max_tile_x = set->img->width / set->tile_size.x;
	max_tile_y = set->img->height / set->tile_size.y;
	if (pos.x >= max_tile_x || pos.y >= max_tile_y)
		return (NULL);
	tile_pos.x = pos.x * set->tile_size.x;
	tile_pos.y = pos.y * set->tile_size.y;
	img = crust_img_crop(set->img, tile_pos, set->tile_size);
	return (img);
}
