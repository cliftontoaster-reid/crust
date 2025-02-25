/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:44:19 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/25 16:53:35 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map/camera.h"

void	camera_move(t_camera *camera, t_2d dest)
{
	if (camera == NULL)
		return ;
	camera->pos = dest;
}
