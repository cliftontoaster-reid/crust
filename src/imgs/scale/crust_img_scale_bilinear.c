/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crust_img_scale_bilinear.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:23:45 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/14 14:28:47 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "img/scale.h"
#include <math.h>
#include <stdlib.h>

static void	getpxls(t_bilinear_context *b, t_img *img)
{
	b->c00 = crust_img_get_pixel(img, (t_2d){b->x0, b->y0});
	b->c10 = crust_img_get_pixel(img, (t_2d){b->x1, b->y0});
	b->c01 = crust_img_get_pixel(img, (t_2d){b->x0, b->y1});
	b->c11 = crust_img_get_pixel(img, (t_2d){b->x1, b->y1});
}

static t_rgba	bilinear_interpolate(t_img *img, double gx, double gy)
{
	t_bilinear_context	b;
	t_rgba				result;

	b.x0 = (int)gx;
	b.y0 = (int)gy;
	b.x1 = b.x0 + (b.x0 < img->width - 1);
	b.y1 = b.y0 + (b.y0 < img->height - 1);
	b.dx = fmax(0.0, fmin(1.0, gx - b.x0));
	b.dy = fmax(0.0, fmin(1.0, gy - b.y0));
	b.w1 = (1 - b.dx) * (1 - b.dy);
	b.w2 = b.dx * (1 - b.dy);
	b.w3 = (1 - b.dx) * b.dy;
	b.w4 = b.dx * b.dy;
	getpxls(&b, img);
	result.r = b.c00.r * b.w1 + b.c10.r * b.w2 + b.c01.r * b.w3 + b.c11.r
		* b.w4;
	result.g = b.c00.g * b.w1 + b.c10.g * b.w2 + b.c01.g * b.w3 + b.c11.g
		* b.w4;
	result.b = b.c00.b * b.w1 + b.c10.b * b.w2 + b.c01.b * b.w3 + b.c11.b
		* b.w4;
	result.a = b.c00.a * b.w1 + b.c10.a * b.w2 + b.c01.a * b.w3 + b.c11.a
		* b.w4;
	return (result);
}

static void	in_loop(t_bilinear_context *b, t_img *img)
{
	b->gy = b->y * b->scale_y;
	b->x = 0;
	while (b->x < b->new_img->width)
	{
		b->gx = b->x * b->scale_x;
		crust_img_put_pixel(b->new_img, (t_2d){b->x, b->y},
			bilinear_interpolate(img, b->gx, b->gy));
		b->x++;
	}
}

t_img	*crust_img_scale_bilinear(t_img *img, t_2d new_size)
{
	t_bilinear_context	b;

	if (!img || new_size.x <= 0 || new_size.y <= 0)
		return (NULL);
	b.new_img = crust_img_new(img->mlx_ptr, new_size.x, new_size.y);
	if (!b.new_img)
		return (NULL);
	if (b.new_img->height > 1)
		b.scale_x = (img->width - 1.0) / (b.new_img->width - 1.0);
	else
		b.scale_x = 0;
	if (b.new_img->height > 1)
		b.scale_y = (img->height - 1.0) / (b.new_img->height - 1.0);
	else
		b.scale_y = 0;
	b.y = 0;
	while (b.y < b.new_img->height)
	{
		in_loop(&b, img);
		b.y++;
	}
	return (b.new_img);
}
