/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crust_set_get_img_offgrid.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:19:40 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/13 15:22:44 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "img/set.h"

t_img	*crust_set_get_img_offgrid(t_set *set, t_2d pos, t_2d size)
{
	t_img	*new_img;

	if (pos.x < 0 || pos.y < 0 || pos.x + size.x > set->img->width || pos.y
		+ size.y > set->img->height)
		return (NULL);
	new_img = crust_img_new(set->mlx_ptr, size.x, size.y);
	if (!new_img)
		return (NULL);
	crust_img_cpy(new_img, set->img, pos, size);
	return (new_img);
}
