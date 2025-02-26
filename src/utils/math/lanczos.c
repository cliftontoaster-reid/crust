/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lanczos.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 12:10:22 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/26 12:10:30 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/math.h"

double	lanczos(double x, int a)
{
	if (fabs(x) >= a)
		return (0.0);
	return (sinc(x) * sinc(x / (double)a));
}
