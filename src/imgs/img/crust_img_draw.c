/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crust_img_draw.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:05:04 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/25 15:16:22 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "img/img.h"

void	crust_img_draw(t_img *dst, t_img *src, t_2d dst_pos)
{
	t_2d	pos;
	t_2d	dpos;
	t_rgba	src_pixel;

	pos = (t_2d){0, 0};
	while (pos.y < src->height)
	{
		pos.x = 0;
		while (pos.x < src->width)
		{
			dpos.x = pos.x + dst_pos.x;
			dpos.y = pos.y + dst_pos.y;
			src_pixel = crust_img_get_pixel(src, pos);
			if (dpos.x >= 0 && dpos.y >= 0 && dpos.x < dst->width
				&& dpos.y < dst->height)
				crust_img_put_pixel(dst, dpos, src_pixel);
			pos.x++;
		}
		pos.y++;
	}
}
