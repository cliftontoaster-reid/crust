/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crust_img_scale_lanczos.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:26:31 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/14 14:49:29 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "img/scale.h"
#include <math.h>
#include <stdlib.h>

static void	process_pixel(t_lanczos_context *l, t_img *img, t_2d new_pos,
		double scale_x)
{
	l->orig_x = (new_pos.x + 0.5) * scale_x - 0.5;
	l->sum_r = 0.0;
	l->sum_g = 0.0;
	l->sum_b = 0.0;
	l->sum_a = 0.0;
	l->weight_sum = 0.0;
	laz_loop_one(l, img);
	if (l->weight_sum > 0)
	{
		l->new_color.r = (uint8_t)fmin(fmax(l->sum_r / l->weight_sum, 0), 255);
		l->new_color.g = (uint8_t)fmin(fmax(l->sum_g / l->weight_sum, 0), 255);
		l->new_color.b = (uint8_t)fmin(fmax(l->sum_b / l->weight_sum, 0), 255);
		l->new_color.a = (uint8_t)fmin(fmax(l->sum_a / l->weight_sum, 0), 255);
	}
	else
		l->new_color = crust_img_get_pixel(img, (t_2d){(int)l->orig_x,
				(int)l->orig_y});
	crust_img_put_pixel(l->new_img, new_pos, l->new_color);
}

static void	process_row(t_process_row_args args)
{
	int	x_new;

	x_new = 0;
	while (x_new < args.new_size.x)
	{
		args.l->orig_y = (args.y_new + 0.5) * args.scale_y - 0.5;
		process_pixel(args.l, args.img, (t_2d){x_new, args.y_new},
			args.scale_x);
		x_new++;
	}
}

t_img	*crust_img_scale_lanczos(t_img *img, t_2d new_size)
{
	t_lanczos_context	l;
	double				scale_x;
	double				scale_y;
	int					y_new;
	t_process_row_args	args;

	l.sum_r = 0.0;
	l.sum_g = 0.0;
	l.sum_b = 0.0;
	if (!img || new_size.x <= 0 || new_size.y <= 0)
		return (NULL);
	l.new_img = crust_img_new(img->mlx_ptr, new_size.x, new_size.y);
	if (!l.new_img)
		return (NULL);
	scale_x = (double)img->width / new_size.x;
	scale_y = (double)img->height / new_size.y;
	y_new = 0;
	while (y_new < new_size.y)
	{
		args = (t_process_row_args){&l, img, y_new, new_size, scale_x, scale_y};
		process_row(args);
		y_new++;
	}
	return (l.new_img);
}
