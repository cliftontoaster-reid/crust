/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crust_img_draw.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:05:04 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/11 15:05:17 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "img.h"

void	crust_img_draw(t_img *dst, t_img *src, t_2d dst_pos)
{
	t_2d	pos;
	t_2d	src_pos;

	pos = (t_2d){0, 0};
	while (pos.y < dst->height)
	{
		pos.x = 0;
		while (pos.x < dst->width)
		{
			src_pos = (t_2d){pos.x % src->width, pos.y % src->height};
			img_pixel_put(dst, dst_pos.x + pos.x, dst_pos.y + pos.y,
				img_pixel_get(src, src_pos.x, src_pos.y));
			pos.x++;
		}
		pos.y++;
	}
}
