/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crust_set_get_imgs_by_pos.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:22:47 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/14 11:52:01 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "img/set.h"

t_img	*crust_set_get_imgs_by_pos(t_set *set, t_2d start, t_2d end)
{
	t_img	*img;
	t_2d	tile_pos;
	t_2d	size;

	if (!set || start.x < 0 || start.y < 0 || end.x < 0 || end.y < 0)
		return (NULL);
	tile_pos.x = start.x * set->tile_size.x;
	tile_pos.y = start.y * set->tile_size.y;
	size.x = (end.x - start.x) * set->tile_size.x;
	size.y = (end.y - start.y) * set->tile_size.y;
	img = crust_img_crop(set->img, tile_pos, size);
	return (img);
}
