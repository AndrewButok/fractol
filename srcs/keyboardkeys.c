/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboardkeys.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 12:50:00 by abutok            #+#    #+#             */
/*   Updated: 2018/03/10 12:50:00 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#define F_KEY 3
#define UP_KEY 126
#define DOWN_KEY 125
#define LEFT_KEY 123
#define RIGHT_KEY 124
#define ONE_KEY 18
#define TWO_KEY 19
#define THREE_KEY 20
#define FOUR_KEY 21
#define FIVE_KEY 23
#define SIX_KEY 22
#define SEVEN_KEY 26
#define Q_KEY 12
#define W_KEY 13
#define E_KEY 14
#define R_KEY 15
#define T_KEY 17
#define A_KEY 0
#define D_KEY 2
#define ESC_KEY 53

static cl_kernel	select_kernel(int key, t_view *view)
{
	if (key == ONE_KEY)
		return (clCreateKernel(view->cl->program,
				"Mandelbrot", NULL));
	else if (key == TWO_KEY)
		return (clCreateKernel(view->cl->program,
				"Julia", NULL));
	else if (key == THREE_KEY)
		return (clCreateKernel(view->cl->program,
				"Newton", NULL));
	else if (key == FOUR_KEY)
		return (clCreateKernel(view->cl->program,
				"Interstellar", NULL));
	else if (key == FIVE_KEY)
		return (clCreateKernel(view->cl->program,
				"Burningship", NULL));
	else if (key == SIX_KEY)
		return (clCreateKernel(view->cl->program,
				"Butterfly", NULL));
	else if (key == SEVEN_KEY)
		return (clCreateKernel(view->cl->program,
				"Mandelbrot3", NULL));
	else
		return (clCreateKernel(view->cl->program,
				"FabsJulia", NULL));
}

void				set_defaults(t_view *view)
{
	view->param[0] = 10;
	view->param[1] = 1;
	view->param[2] = WIN_WIDTH / 2;
	view->param[3] = WIN_HEIGHT / 2;
	view->param[4] = 0;
	view->param[5] = 0;
	view->param[6] = view->size_line;
	view->param[7] = 400;
	view->param[8] = 700;
	view->param[9] = 0x0;
	view->freeze = 0;
}

static void			change_kernel(int key, t_view *view)
{
	clReleaseKernel(view->cl->kernel);
	view->cl->kernel = select_kernel(key, view);
	clSetKernelArg(view->cl->kernel, 0, sizeof(cl_mem), &view->cl->bufscr);
	clSetKernelArg(view->cl->kernel, 1, sizeof(cl_mem), &view->cl->bufparam);
	set_defaults(view);
}

static void			set_color(int key, t_view *view)
{
	if (key == Q_KEY)
		view->param[9] = 0xffffff;
	if (key == W_KEY)
		view->param[9] = 0xff0000;
	if (key == E_KEY)
		view->param[9] = 0xff00;
	if (key == R_KEY)
		view->param[9] = 0xff;
	if (key == T_KEY)
		view->param[9] = 0;
	if (key == A_KEY)
		view->param[9] = 0xffff00;
}

int					do_keyboard(int key, t_view *view)
{
	if (key == F_KEY)
		view->freeze = view->freeze == 1 ? 0 : 1;
	if (key == LEFT_KEY || key == RIGHT_KEY)
		view->param[4] += (key == LEFT_KEY ? 10 : -10) / (100 * view->param[1]);
	if (key == DOWN_KEY || key == UP_KEY)
		view->param[5] += (key == DOWN_KEY ? -10 : 10) / (100 * view->param[1]);
	if (key <= 28 && key >= 18 && key != 24 && key != 27 && key != 25)
		change_kernel(key, view);
	if (key == ESC_KEY)
		exit_x(view);
	if (key == D_KEY)
		set_defaults(view);
	set_color(key, view);
	fract_redraw(view);
	return (1);
}
