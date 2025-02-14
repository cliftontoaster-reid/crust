/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crust_set_get_img.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:09:54 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/14 11:51:17 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "img/set.h"

t_img	*crust_set_get_img(t_set *set, long idx)
{
	t_img	*img;
	t_2d	pos;
	int		tiles_per_row;

	if (!set || idx < 0)
		return (NULL);
	tiles_per_row = set->img->width / set->tile_size.x;
	pos.x = (idx % tiles_per_row) * set->tile_size.x;
	pos.y = (idx / tiles_per_row) * set->tile_size.y;
	img = crust_img_crop(set->img, pos, set->tile_size);
	return (img);
}
