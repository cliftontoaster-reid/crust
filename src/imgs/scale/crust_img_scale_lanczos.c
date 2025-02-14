/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crust_img_scale_lanczos.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:26:31 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/13 23:35:24 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "img/img.h"
#include <math.h>
#include <stdlib.h>

#define LANCZOS_A 3
#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

static inline int	clamp(int value, int min, int max)
{
	return (value < min) ? min : (value > max ? max : value);
}

static double	sinc(double x)
{
	if (fabs(x) < 1e-7)
		return (1.0);
	return (sin(M_PI * x) / (M_PI * x));
}

static double	lanczos(double x, int a)
{
	if (fabs(x) >= a)
		return (0.0);
	return (sinc(x) * sinc(x / (double)a));
}

__attribute__((visibility("hidden"))) t_img *crust_img_scale_lanczos(t_img *img,
	t_2d new_size)
{
	t_img	*new_img;
	double	orig_x;
	double	orig_y;
	double	sum_r;
	double	sum_g;
	double	sum_b;
	double	sum_a;
	double	weight_sum;
	double	wx;
	double	wy;
	double	weight;
	t_2d	pos;
	t_rgba	c;
	t_rgba	new_color;

	sum_r = 0.0;
	sum_g = 0.0;
	sum_b = 0.0;
	double scale_x, scale_y;
	int x_new, y_new;
	if (!img || new_size.x <= 0 || new_size.y <= 0)
		return (NULL);
	new_img = crust_img_new(img->mlx_ptr, new_size.x, new_size.y);
	if (!new_img)
		return (NULL);
	scale_x = (double)img->width / new_size.x;
	scale_y = (double)img->height / new_size.y;
	for (y_new = 0; y_new < new_size.y; y_new++)
	{
		for (x_new = 0; x_new < new_size.x; x_new++)
		{
			orig_x = (x_new + 0.5) * scale_x - 0.5;
			orig_y = (y_new + 0.5) * scale_y - 0.5;
			sum_r = 0.0, sum_g = 0.0, sum_b = 0.0, sum_a = 0.0;
			weight_sum = 0.0;
			// Loop over the Lanczos kernel window
			for (int m = (int)floor(orig_y - LANCZOS_A
					+ 1); m <= (int)floor(orig_y + LANCZOS_A); m++)
			{
				for (int n = (int)floor(orig_x - LANCZOS_A
						+ 1); n <= (int)floor(orig_x + LANCZOS_A); n++)
				{
					wx = lanczos(orig_x - n, LANCZOS_A);
					wy = lanczos(orig_y - m, LANCZOS_A);
					weight = wx * wy;
					pos.x = clamp(n, 0, img->width - 1);
					pos.y = clamp(m, 0, img->height - 1);
					c = crust_img_get_pixel(img, pos);
					sum_r += c.r * weight;
					sum_g += c.g * weight;
					sum_b += c.b * weight;
					sum_a += c.a * weight;
					weight_sum += weight;
				}
			}
			if (weight_sum > 0)
			{
				new_color.r = (uint8_t)fmin(fmax(sum_r / weight_sum, 0), 255);
				new_color.g = (uint8_t)fmin(fmax(sum_g / weight_sum, 0), 255);
				new_color.b = (uint8_t)fmin(fmax(sum_b / weight_sum, 0), 255);
				new_color.a = (uint8_t)fmin(fmax(sum_a / weight_sum, 0), 255);
			}
			else
			{
				new_color = crust_img_get_pixel(img, (t_2d){(int)orig_x,
						(int)orig_y});
			}
			crust_img_put_pixel(new_img, (t_2d){x_new, y_new}, new_color);
		}
	}
	return (new_img);
}
