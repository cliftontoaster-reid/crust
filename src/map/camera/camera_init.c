/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:25:53 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/25 16:51:36 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map/camera.h"

t_camera	*camera_init(t_2d pos, t_2d size)
{
	t_camera	*camera;

	camera = malloc(sizeof(t_camera));
	if (!camera)
		return (NULL);
	ft_bzero(camera, sizeof(t_camera));
	camera->pos.x = pos.x;
	camera->pos.y = pos.y;
	(void)0;
	camera->size.x = size.x;
	camera->size.y = size.y;
	return (camera);
}
