/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crust_img_scale.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:53:49 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/13 23:34:47 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "img/scale.h"

t_img	*crust_img_scale(t_img *img, t_2d new_size, t_crust_img_scale_algo algo)
{
	if (!img || new_size.x <= 0 || new_size.y <= 0)
		return (NULL);
	if (algo == CRUST_IMG_SCALE_NEAREST)
		return (crust_img_scale_nearest(img, new_size));
	else if (algo == CRUST_IMG_SCALE_BILINEAR)
		return (crust_img_scale_bilinear(img, new_size));
	else if (algo == CRUST_IMG_SCALE_LANCZOS)
		return (crust_img_scale_lanczos(img, new_size));
	return (NULL);
}
