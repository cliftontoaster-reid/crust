/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crust_img_crop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:12:45 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/13 22:25:00 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "img/img.h"

t_img	*crust_img_crop(t_img *img, t_2d pos, t_2d size)
{
	t_img	*new_img;
	t_2d	cpos;
	t_rgba	pixel;

	if (!img || pos.x < 0 || pos.y < 0 || size.x <= 0 || size.y <= 0)
		return (NULL);
	if (pos.x + size.x > img->width || pos.y + size.y > img->height)
		return (NULL);
	new_img = crust_img_new(img->mlx_ptr, size.x, size.y);
	if (!new_img)
		return (NULL);
	cpos.y = 0;
	while (cpos.y < size.y)
	{
		cpos.x = 0;
		while (cpos.x < size.x)
		{
			pixel = crust_img_get_pixel(img, (t_2d){pos.x + cpos.x, pos.y
					+ cpos.y});
			crust_img_put_pixel(new_img, cpos, pixel);
			cpos.x++;
		}
		cpos.y++;
	}
	return (new_img);
}
