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
# include <math.h>
# include <OpenCL/cl.h>
# define WIN_HEIGHT	1080
# define WIN_WIDTH	1920

typedef struct	s_cl
{
	cl_device_id		device;
	cl_context			context;
	cl_command_queue	queue;
	cl_program			program;
	cl_kernel			kernel;
	cl_mem				bufscr;
	cl_mem				bufparam;
	size_t				works;

}				t_cl;

typedef struct	s_view
{
	void				*mlx;
	void				*win;
	void				*img;
	cl_int				*scene;
	cl_float			*param;
	int					bits_per_pixel;
	int					endian;
	int					freeze;
	int					is_pressed;
	int					x;
	int					y;
	int					size_line;
	t_cl				*cl;

}				t_view;

void			cl_init(t_view *view, char *frac);
void			cl_run(t_view *view);
void			cl_read_buffer(t_view *view);
void			fract_redraw(t_view *view);
int				do_mouse(int button, int x, int y, t_view *view);
int				do_mouse_m(int x, int y, t_view *view);
int				unpress(int key, int x, int y, t_view *view);
int				do_keyboard(int key, t_view *view);
void			set_defaults(t_view *view);
int				exit_x(t_view *view);

#endif
