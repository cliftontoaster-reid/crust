/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crust_img_cpy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:15:26 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/14 14:51:33 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "img/set.h"

void	crust_img_cpy(t_img *dst, t_img *src, t_2d pos, t_2d size)
{
	int		y;
	int		x;
	t_2d	src_pos;
	t_2d	dst_pos;
	t_rgba	pixel;

	y = 0;
	while (y < size.y && (pos.y + y) < dst->height && y < src->height)
	{
		x = 0;
		while (x < size.x && (pos.x + x) < dst->width && x < src->width)
		{
			src_pos.x = x;
			src_pos.y = y;
			dst_pos.x = pos.x + x;
			dst_pos.y = pos.y + y;
			pixel = crust_img_get_pixel(src, src_pos);
			crust_img_put_pixel(dst, dst_pos, pixel);
			x++;
		}
		y++;
	}
}
