/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:28:52 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/25 16:53:46 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map/camera.h"

void	camera_free(t_camera *camera)
{
	if (camera == NULL)
		return ;
	ft_bzero(camera, sizeof(t_camera));
	free(camera);
}
