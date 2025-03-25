/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crust_img_draw.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:05:04 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/25 15:39:32 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "img/img.h"

/**
 * Check if a destination position is within bounds
 */
static int	is_in_bounds(t_img *dst, t_2d pos)
{
	return (pos.x >= 0 && pos.y >= 0 && pos.x < dst->width
		&& pos.y < dst->height);
}

/**
 * Check if a color is pitch black
 */
static int	is_pitch_black(t_rgba color)
{
	return (color.r == 0 && color.g == 0 && color.b == 0);
}

/**
 * Process a single pixel during drawing
 */
static void	process_pixel(t_img *dst, t_img *src, t_2d src_pos, t_2d dst_pos)
{
	t_rgba	src_pixel;

	src_pixel = crust_img_get_pixel(src, src_pos);
	if (!is_pitch_black(src_pixel))
	{
		crust_img_put_pixel(dst, dst_pos, src_pixel);
	}
}

void	crust_img_draw(t_img *dst, t_img *src, t_2d dst_pos)
{
	t_2d	pos;
	t_2d	dpos;

	pos = (t_2d){0, 0};
	while (pos.y < src->height)
	{
		pos.x = 0;
		while (pos.x < src->width)
		{
			dpos.x = pos.x + dst_pos.x;
			dpos.y = pos.y + dst_pos.y;
			if (is_in_bounds(dst, dpos))
				process_pixel(dst, src, pos, dpos);
			pos.x++;
		}
		pos.y++;
	}
}
