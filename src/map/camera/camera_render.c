/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:29:29 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/25 16:52:45 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "img/img.h"
#include "map/camera.h"

t_img	*camera_render(t_camera *camera, t_img *img, void *mlx)
{
	t_img	*render;
	t_2d	pos;
	t_2d	img_pos;

	render = crust_img_new(mlx, camera->size.x, camera->size.y);
	if (!render)
		return (NULL);
	ft_bzero(&pos, sizeof(t_2d));
	while (pos.y < camera->size.y)
	{
		pos.x = 0;
		while (pos.x < camera->size.x)
		{
			img_pos.x = camera->pos.x - (camera->size.x / 2) + pos.x;
			img_pos.y = camera->pos.y - (camera->size.y / 2) + pos.y;
			if (img_pos.x >= 0 && img_pos.x < img->width && img_pos.y >= 0
				&& img_pos.y < img->height)
				crust_img_put_pixel(render, pos, crust_img_get_pixel(img,
						img_pos));
			pos.x++;
		}
		pos.y++;
	}
	return (render);
}
