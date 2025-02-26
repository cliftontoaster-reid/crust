/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crust_img_cpy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:15:26 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/26 11:48:22 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "img/set.h"

static void	pixel_move(t_img *dst, t_img *src, t_2d dst_pos, t_2d src_pos)
{
	t_rgba	pixel;

	pixel = crust_img_get_pixel(src, src_pos);
	crust_img_put_pixel(dst, dst_pos, pixel);
}

void	crust_img_cpy(t_img *dst, t_img *src, t_2d pos, t_2d size)
{
	int		y;
	int		x;
	t_2d	src_pos;
	t_2d	dst_pos;

	y = 0;
	while (y < size.y)
	{
		x = 0;
		while (x < size.x)
		{
			src_pos.x = pos.x + x;
			src_pos.y = pos.y + y;
			dst_pos.x = x;
			dst_pos.y = y;
			pixel_move(dst, src, dst_pos, src_pos);
			x++;
		}
		y++;
	}
}
