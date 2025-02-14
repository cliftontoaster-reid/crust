/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crust_set_drop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:08:36 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/13 12:25:44 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "img/set.h"

void	crust_set_drop(t_set *set)
{
	if (!set)
		return ;
	if (set->img)
		crust_img_drop(set->img);
	free(set);
}
