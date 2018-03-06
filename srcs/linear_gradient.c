/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_gradient.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 09:18:00 by abutok            #+#    #+#             */
/*   Updated: 2017/12/05 09:18:00 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
**	linear_gradient function return value of color for i point between start
**	and end point.
*/

int			linear_gradient(t_point *start, t_point *end, bool ck, int i)
{
	double		d[4];
	t_color		color;

	d[1] = end->color.spectrum.red - start->color.spectrum.red;
	d[2] = end->color.spectrum.green - start->color.spectrum.green;
	d[3] = end->color.spectrum.blue - start->color.spectrum.blue;
	d[0] = end->color.spectrum.alpha - start->color.spectrum.alpha;
	d[1] /= (ck ? (end->x - start->x) : (end->y - start->y));
	d[2] /= (ck ? (end->x - start->x) : (end->y - start->y));
	d[3] /= (ck ? (end->x - start->x) : (end->y - start->y));
	d[0] /= (ck ? (end->x - start->x) : (end->y - start->y));
	color = start->color;
	color.spectrum.red += (unsigned char)round(d[1] * i);
	color.spectrum.green += (unsigned char)round(d[2] * i);
	color.spectrum.blue += (unsigned char)round(d[3] * i);
	color.spectrum.alpha += (unsigned char)round(d[0] * i);
	return (color.color);
}
