/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crust_img_scale_lanczos.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+    */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:26:31 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/26 12:30:00 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "img/img.h"
#include "utils/math.h"
#include <math.h>
#include <stdlib.h>

#define LANCZOS_A 3

/*
 * This function processes the inner n-loop for a given row.
 */
static void	process_n_loop(t_img *img, t_lanczos_interpolate *li, int current_m)
{
	li->n_start = (int)floor(li->orig_x - LANCZOS_A + 1);
	li->n_end = (int)floor(li->orig_x + LANCZOS_A);
	li->n = li->n_start;
	while (li->n <= li->n_end)
	{
		li->wx = lanczos(li->orig_x - li->n, LANCZOS_A);
		li->wy = lanczos(li->orig_y - current_m, LANCZOS_A);
		li->weight = li->wx * li->wy;
		li->pos.x = clamp(li->n, 0, img->width - 1);
		li->pos.y = clamp(current_m, 0, img->height - 1);
		li->c = crust_img_get_pixel(img, li->pos);
		li->sum_r += li->c.r * li->weight;
		li->sum_g += li->c.g * li->weight;
		li->sum_b += li->c.b * li->weight;
		li->sum_a += li->c.a * li->weight;
		li->weight_sum += li->weight;
		li->n++;
	}
}

/*
 * This helper function performs the inner Lanczos kernel loop.
 * It iterates over rows (m) and for each row calls process_n_loop.
 */
static void	lanczos_kernel_loop(t_img *img, t_lanczos_interpolate *li)
{
	li->m_start = (int)floor(li->orig_y - LANCZOS_A + 1);
	li->m_end = (int)floor(li->orig_y + LANCZOS_A);
	li->sum_r = 0.0;
	li->sum_g = 0.0;
	li->sum_b = 0.0;
	li->sum_a = 0.0;
	li->weight_sum = 0.0;
	li->m = li->m_start;
	while (li->m <= li->m_end)
	{
		process_n_loop(img, li, li->m);
		li->m++;
	}
}

/*
 * This helper function processes one pixel of the new image.
 * It calculates the original coordinate and applies the Lanczos kernel.
 */
static void	process_new_pixels_loop(t_lanczos_interpolate *li, t_img *src)
{
	li->orig_x = (li->x_new + 0.5) * li->scale_x - 0.5;
	li->orig_y = (li->y_new + 0.5) * li->scale_y - 0.5;
	lanczos_kernel_loop(src, li);
	if (li->weight_sum > 0)
	{
		li->new_color.r = (uint8_t)fmin(fmax(li->sum_r / li->weight_sum, 0),
				255);
		li->new_color.g = (uint8_t)fmin(fmax(li->sum_g / li->weight_sum, 0),
				255);
		li->new_color.b = (uint8_t)fmin(fmax(li->sum_b / li->weight_sum, 0),
				255);
		li->new_color.a = (uint8_t)fmin(fmax(li->sum_a / li->weight_sum, 0),
				255);
	}
	else
		li->new_color = crust_img_get_pixel(src, (t_2d){(int)li->orig_x,
				(int)li->orig_y});
	crust_img_put_pixel(li->new_img, (t_2d){li->x_new, li->y_new},
		li->new_color);
	li->x_new++;
}

/*
 * This helper function processes the new image pixels.
 * It extracts the iteration over new image rows and columns.
 */
static void	process_new_pixels(t_img *src, t_lanczos_interpolate *li)
{
	li->y_new = 0;
	while (li->y_new < li->new_height)
	{
		li->x_new = 0;
		while (li->x_new < li->new_width)
		{
			process_new_pixels_loop(li, src);
		}
		li->y_new++;
	}
}

/*
 * Scales an image to a new size using Lanczos interpolation.
 */
t_img	*crust_img_scale_lanczos(t_img *img, t_2d new_size)
{
	t_lanczos_interpolate	li;
	double					scale_x;
	double					scale_y;

	if (!img || new_size.x <= 0 || new_size.y <= 0)
		return (NULL);
	li.new_img = crust_img_new(img->mlx_ptr, new_size.x, new_size.y);
	if (!li.new_img)
		return (NULL);
	scale_x = (double)img->width / new_size.x;
	scale_y = (double)img->height / new_size.y;
	li.scale_x = scale_x;
	li.scale_y = scale_y;
	li.new_width = new_size.x;
	li.new_height = new_size.y;
	process_new_pixels(img, &li);
	return (li.new_img);
}
