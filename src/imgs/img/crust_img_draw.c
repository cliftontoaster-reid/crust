/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crust_img_draw.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:05:04 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/25 15:34:43 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "img/img.h"
#include <stdbool.h>

/**
 * Checks if a position is within the bounds of an image
 */
static bool	is_within_bounds(t_img *img, t_2d pos)
{
	return (pos.x >= 0 && pos.y >= 0 && pos.x < img->width
		&& pos.y < img->height);
}

/**
 * Blends source and destination pixels based on source alpha
 */
static t_rgba	blend_pixels(t_rgba src, t_rgba dst)
{
	t_rgba	result;
	float	alpha_ratio;

	alpha_ratio = src.a / 255.0f;
	result.r = (src.r * alpha_ratio) + (dst.r * (1.0f - alpha_ratio));
	result.g = (src.g * alpha_ratio) + (dst.g * (1.0f - alpha_ratio));
	result.b = (src.b * alpha_ratio) + (dst.b * (1.0f - alpha_ratio));
	result.a = 255;
	return (result);
}

/**
 * Handles drawing a single pixel with alpha blending
 */
static void	draw_pixel(t_img *dst, t_img *src, t_2d src_pos, t_2d dst_pos)
{
	t_rgba	src_pixel;
	t_rgba	dst_pixel;
	t_rgba	blended;

	src_pixel = crust_img_get_pixel(src, src_pos);
	if (src_pixel.a == 0)
		return ;
	if (src_pixel.a == 255)
	{
		crust_img_put_pixel(dst, dst_pos, src_pixel);
		return ;
	}
	dst_pixel = crust_img_get_pixel(dst, dst_pos);
	blended = blend_pixels(src_pixel, dst_pixel);
	crust_img_put_pixel(dst, dst_pos, blended);
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
			if (is_within_bounds(dst, dpos))
				draw_pixel(dst, src, pos, dpos);
			pos.x++;
		}
		pos.y++;
	}
}
