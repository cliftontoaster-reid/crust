/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crust_img_put_pixel.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:33:30 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/13 18:18:28 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "img/img.h"

void	crust_img_put_pixel(t_img *img, t_2d pos, t_rgba color)
{
	unsigned int	int_color;
	int				offset;

	if (pos.x < 0 || pos.x >= img->width || pos.y < 0 || pos.y >= img->height)
		return ;
	// RGBA
	int_color = 0;
	int_color |= color.a << 24;
	int_color |= color.r << 16;
	int_color |= color.g << 8;
	int_color |= color.b;
	offset = pos.y * img->size_line + pos.x * (img->bpp / 8);
	((int *)img->data_ptr)[offset / 4] = int_color;
}
