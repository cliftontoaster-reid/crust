/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crust_img_scale_nearest.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:59:59 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/25 16:54:42 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "img/scale.h"

t_img	*crust_img_scale_nearest(t_img *img, t_2d new_size)
{
	t_img	*new_img;
	t_2d	pos;
	t_rgba	color;

	new_img = crust_img_new(img->mlx_ptr, new_size.x, new_size.y);
	if (!new_img)
		return (NULL);
	pos.y = 0;
	while (pos.y < new_size.y)
	{
		pos.x = 0;
		while (pos.x < new_size.x)
		{
			color = crust_img_get_pixel(img, (t_2d){pos.x * img->width
					/ new_size.x, pos.y * img->height / new_size.y});
			crust_img_put_pixel(new_img, pos, color);
			pos.x++;
		}
		pos.y++;
	}
	return (new_img);
}
