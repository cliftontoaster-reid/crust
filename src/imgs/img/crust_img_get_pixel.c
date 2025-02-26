/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crust_img_get_pixel.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:45:39 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/26 20:25:04 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "img/img.h"

t_rgba	crust_img_get_pixel(t_img *img, t_2d pos)
{
	int		offset;
	t_rgba	color;

	if (pos.x < 0 || pos.x >= img->width || pos.y < 0 || pos.y >= img->height)
		return ((t_rgba){0, 0, 0, 0});
	offset = (pos.y * img->size_line + pos.x * (img->bpp / 8));
	color.a = ((uint8_t *)img->data_ptr)[offset + 3];
	color.r = ((uint8_t *)img->data_ptr)[offset + 2];
	color.g = ((uint8_t *)img->data_ptr)[offset + 1];
	color.b = ((uint8_t *)img->data_ptr)[offset];
	return (color);
}
