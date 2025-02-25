/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:42:25 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/14 14:46:29 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "img/scale.h"

static inline int	clamp(int value, int min, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
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

void	laz_loop_one(t_lanczos_context *l, t_img *img)
{
	int	m;
	int	n;

	m = (int)floor(l->orig_y - LANCZOS_A + 1);
	while (m <= (int)floor(l->orig_y + LANCZOS_A))
	{
		n = (int)floor(l->orig_x - LANCZOS_A + 1);
		while (n <= (int)floor(l->orig_x + LANCZOS_A))
		{
			l->wx = lanczos(l->orig_x - n, LANCZOS_A);
			l->wy = lanczos(l->orig_y - m, LANCZOS_A);
			l->weight = l->wx * l->wy;
			l->pos.x = clamp(n, 0, img->width - 1);
			l->pos.y = clamp(m, 0, img->height - 1);
			l->c = crust_img_get_pixel(img, l->pos);
			l->sum_r += l->c.r * l->weight;
			l->sum_g += l->c.g * l->weight;
			l->sum_b += l->c.b * l->weight;
			l->sum_a += l->c.a * l->weight;
			l->weight_sum += l->weight;
			n++;
		}
		m++;
	}
}
