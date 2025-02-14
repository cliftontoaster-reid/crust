/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crust_set_get_imgs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:24:33 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/14 11:51:58 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "img/set.h"

t_img	*crust_set_get_imgs(t_set *set, long start, long end)
{
	t_img	*img;
	t_2d	pos;
	t_2d	size;

	if (!set || start < 0 || end < 0)
		return (NULL);
	if (start > end)
		return (NULL);
	pos.x = (start % (set->img->width / set->tile_size.x)) * set->tile_size.x;
	pos.y = (start / (set->img->width / set->tile_size.x)) * set->tile_size.y;
	size.x = ((end % (set->img->width / set->tile_size.x)) + 1)
		* set->tile_size.x - pos.x;
	size.y = ((end / (set->img->width / set->tile_size.x)) + 1)
		* set->tile_size.y - pos.y;
	img = crust_img_crop(set->img, pos, size);
	return (img);
}
