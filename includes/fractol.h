/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 10:58:00 by abutok            #+#    #+#             */
/*   Updated: 2018/03/04 10:58:00 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include "libft.h"
# include "get_next_line.h"
# include <errno.h>
# include <stdio.h>
# include <mlx.h>
# include <stdbool.h>
# include <math.h>
# include <OpenCL/cl.h>
# define WIN_HEIGHT	800
# define WIN_WIDTH	1200

typedef union			u_color
{
	int		color;
	struct
	{
		unsigned char	blue;
		unsigned char	green;
		unsigned char	red;
		unsigned char	alpha;
	}		spectrum;
}						t_color;
typedef struct	s_point
{
	int			x;
	int			y;
	t_color	color;
}				t_point;

typedef struct	s_cl
{
	cl_device_id		device;
	cl_context			context;
	cl_command_queue	queue;
	cl_program			program;
	cl_kernel			kernel;
	cl_mem				bufscr;
	cl_mem				bufparam;
	size_t 				works;

}				t_cl;

typedef struct	s_view
{
	void	*mlx;
	void	*win;
	void	*img;
	cl_int		*scene;
	cl_double 	*param;
	int		bits_per_pixel;
	int		endian;
	int		x;
	int		y;
	int		size_line;
	t_cl	*cl;

}				t_view;

t_cl			*cl_init(t_view *view, char *frac);
void			img_pixel_put(t_view *view, int x, int y, t_color color);
int				linear_gradient(t_point *start, t_point *end, bool ck, int i);


#endif