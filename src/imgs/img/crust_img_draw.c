/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crust_img_draw.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:05:04 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/11 15:11:21 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "img/img.h"

void	crust_img_draw(t_img *dst, t_img *src, t_2d dst_pos)
{
	t_2d	pos;
	t_2d	dpos;
	t_rgba	src_pixel;

	pos = (t_2d){0, 0};
	while (pos.y < dst->height)
	{
		pos.x = 0;
		while (pos.x < dst->width)
		{
			dpos.x = pos.x + dst_pos.x;
			dpos.y = pos.y + dst_pos.y;
			src_pixel = crust_img_get_pixel(src, pos);
			crust_img_put_pixel(dst, dpos, src_pixel);
			pos.x++;
		}
		pos.y++;
	}
}
