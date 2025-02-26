/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crust_img_scale_bilinear.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:23:45 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/26 11:43:16 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "img/img.h"
#include <math.h>
#include <stdlib.h>

static t_rgba	bilinear_addition(t_bilinear_interpolate bi)
{
	t_rgba	result;

	result.r = (uint8_t)(bi.c00.r * bi.w1 + bi.c10.r * bi.w2);
	result.r += (uint8_t)(bi.c01.r * bi.w3 + bi.c11.r * bi.w4 + 0.5f);
	result.g = (uint8_t)(bi.c00.g * bi.w1 + bi.c10.g * bi.w2);
	result.g += (uint8_t)(bi.c01.g * bi.w3 + bi.c11.g * bi.w4 + 0.5f);
	result.b = (uint8_t)(bi.c00.b * bi.w1 + bi.c10.b * bi.w2);
	result.b += (uint8_t)(bi.c01.b * bi.w3 + bi.c11.b * bi.w4 + 0.5f);
	result.a = (uint8_t)(bi.c00.a * bi.w1 + bi.c10.a * bi.w2);
	result.a += (uint8_t)(bi.c01.a * bi.w3 + bi.c11.a * bi.w4 + 0.5f);
	return (result);
}

static t_rgba	bilinear_interpolate(t_img *img, double gx, double gy)
{
	t_bilinear_interpolate	bi;
	t_rgba					result;
	double					dx;

	bi.x0 = (int)gx;
	bi.y0 = (int)gy;
	bi.x1 = bi.x0 + (bi.x0 < img->width - 1);
	bi.y1 = bi.y0 + (bi.y0 < img->height - 1);
	dx = fmax(0.0, fmin(1.0, gx - bi.x0));
	bi.dy = fmax(0.0, fmin(1.0, gy - bi.y0));
	bi.w1 = (1 - dx) * (1 - bi.dy);
	bi.w2 = dx * (1 - bi.dy);
	bi.w3 = (1 - dx) * bi.dy;
	bi.w4 = dx * bi.dy;
	bi.c00 = crust_img_get_pixel(img, (t_2d){bi.x0, bi.y0});
	bi.c10 = crust_img_get_pixel(img, (t_2d){bi.x1, bi.y0});
	bi.c01 = crust_img_get_pixel(img, (t_2d){bi.x0, bi.y1});
	bi.c11 = crust_img_get_pixel(img, (t_2d){bi.x1, bi.y1});
	result = bilinear_addition(bi);
	return (result);
}

static void	loop(t_bilinear_interpolate *bi, t_img *img)
{
	while (bi->y < bi->new_img->height)
	{
		bi->gy = bi->y * bi->scale_y;
		bi->x = 0;
		while (bi->x < bi->new_img->width)
		{
			bi->gx = bi->x * bi->scale_x;
			(void)"Direct calculation avoids error accumulation";
			crust_img_put_pixel(bi->new_img, (t_2d){bi->x, bi->y},
				bilinear_interpolate(img, bi->gx, bi->gy));
			bi->x++;
		}
		bi->y++;
	}
}

t_img	*crust_img_scale_bilinear(t_img *img, t_2d new_size)
{
	t_bilinear_interpolate	bi;

	if (!img || new_size.x <= 0 || new_size.y <= 0)
		return (NULL);
	bi.new_img = crust_img_new(img->mlx_ptr, new_size.x, new_size.y);
	if (!bi.new_img)
		return (NULL);
	if ((bi.new_img->width > 1))
		bi.scale_x = (img->width - 1.0) / (bi.new_img->width - 1.0);
	else
		bi.scale_x = 0;
	if (bi.new_img->height > 1)
		bi.scale_y = ((img->height - 1.0) / (bi.new_img->height - 1.0));
	else
		bi.scale_y = 0;
	bi.y = 0;
	loop(&bi, img);
	return (bi.new_img);
}
