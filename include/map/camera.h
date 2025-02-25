/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:22:39 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/25 16:52:58 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "img/img.h"

typedef struct s_camera
{
	t_2d	pos;
	t_2d	size;
}			t_camera;

t_camera	*camera_init(t_2d pos, t_2d size);
void		camera_free(t_camera *camera);

t_img		*camera_render(t_camera *camera, t_img *img, void *mlx);
void		camera_move(t_camera *camera, t_2d dest);
void		camera_resize(t_camera *camera, t_2d size);

#endif
