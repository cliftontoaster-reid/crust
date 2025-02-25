/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crust_img_scale_bilinear.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:23:45 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/25 16:54:42 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "img/img.h"
#include <math.h>
#include <stdlib.h>

static t_rgba	bilinear_interpolate(t_img *img, double gx, double gy)
{
	int		x0;
	int		y0;
	int		x1;
	int		y1;
	double	dy;
	double	w1;
	double	w2;
	double	w3;
	double	w4;
	t_rgba	c00;
	t_rgba	c10;
	t_rgba	c01;
	t_rgba	c11;

	x0 = (int)gx;
	y0 = (int)gy;
	x1 = x0 + (x0 < img->width - 1);
	y1 = y0 + (y0 < img->height - 1);
	double dx = fmax(0.0, fmin(1.0, gx - x0)); // Clamp dx/dy
	dy = fmax(0.0, fmin(1.0, gy - y0));
	w1 = (1 - dx) * (1 - dy);
	w2 = dx * (1 - dy);
	w3 = (1 - dx) * dy;
	w4 = dx * dy;
	c00 = crust_img_get_pixel(img, (t_2d){x0, y0});
	c10 = crust_img_get_pixel(img, (t_2d){x1, y0});
	c01 = crust_img_get_pixel(img, (t_2d){x0, y1});
	c11 = crust_img_get_pixel(img, (t_2d){x1, y1});
	return ((t_rgba){.r = (uint8_t)(c00.r * w1 + c10.r * w2 + c01.r * w3 + c11.r
			* w4 + 0.5f), .g = (uint8_t)(c00.g * w1 + c10.g * w2 + c01.g * w3
			+ c11.g * w4 + 0.5f), .b = (uint8_t)(c00.b * w1 + c10.b * w2 + c01.b
			* w3 + c11.b * w4 + 0.5f), .a = (uint8_t)(c00.a * w1 + c10.a * w2
			+ c01.a * w3 + c11.a * w4 + 0.5f)});
}

t_img	*crust_img_scale_bilinear(t_img *img, t_2d new_size)
{
	t_img	*new_img;
	double	scale_x;
	double	scale_y;
	int		x;
	int		y;
	double	gy;
	double	gx;

	if (!img || new_size.x <= 0 || new_size.y <= 0)
		return (NULL);
	new_img = crust_img_new(img->mlx_ptr, new_size.x, new_size.y);
	if (!new_img)
		return (NULL);
	scale_x = (new_img->width > 1) ? ((img->width - 1.0) / (new_img->width
				- 1.0)) : 0;
	scale_y = (new_img->height > 1) ? ((img->height - 1.0) / (new_img->height
				- 1.0)) : 0;
	y = 0;
	while (y < new_img->height)
	{
		gy = y * scale_y;
		x = 0;
		while (x < new_img->width)
		{
			gx = x * scale_x;
			// Direct calculation avoids error accumulation
			crust_img_put_pixel(new_img, (t_2d){x, y}, bilinear_interpolate(img,
					gx, gy));
			x++;
		}
		y++;
	}
	return (new_img);
}
