/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_resize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:45:36 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/25 16:53:22 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map/camera.h"

void	camera_resize(t_camera *camera, t_2d size)
{
	if (size.x <= 0 || size.y <= 0)
		return ;
	if (camera == NULL)
		return ;
	camera->size = size;
}
