/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 12:10:00 by abutok            #+#    #+#             */
/*   Updated: 2018/03/06 12:10:00 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

const char *str = {
				"kernel void mandel(global int *scene, global float *pts, global int *nit)"
				"{"
				"	int		id = get_global_id(0);"
				"	float	r, im, rp;"
				"	int		it;"
				""
				"	r = 0.0f;"
				"	it = 0;"
				"	im = 0.0f;"
				"	while ((r * r + im * im) < 16.0f && (it++ < nit[0]))"
				"	{"
				"		rp = r;"
				"		r = (r * r) - (im * im) + pts[id * 2];"
				"		im = (2 * rp * im) + pts[id * 2 + 1];"
				"	}"
				"	if (it < nit[0])"
				"		scene[id] = it / (float)nit[0] * 0xffffff;"
				"	else"
				"		scene[id] = 0xffffff;"
				"}"
};

t_cl	*cl_init(t_view *view, char *frac)
{
	t_cl	*cl;
	int		err;

	cl = (t_cl*)malloc(sizeof(t_cl));

	err = clGetDeviceIDs(NULL, CL_DEVICE_TYPE_GPU, 1, &(cl->device), NULL);
	cl->context = clCreateContext(NULL, 1, &cl->device, NULL, NULL, &err);
	cl->queue = clCreateCommandQueue(cl->context, cl->device, 0, &err);
	cl->bufscr = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
			sizeof(cl_int) * WIN_HEIGHT * WIN_WIDTH, NULL, &err);
	cl->bufpts = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
			sizeof(cl_float) * WIN_HEIGHT * WIN_WIDTH * 2, NULL, &err);
	cl->bufit = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
			sizeof(cl_int), NULL, &err);
	cl->program = clCreateProgramWithSource(cl->context, 1, &str, NULL, &err);
	err = clBuildProgram(cl->program, 1, &cl->device, NULL, NULL, NULL);
	cl->kernel = clCreateKernel(cl->program, "mandel", &err);
	err = clEnqueueWriteBuffer(cl->queue,cl->bufscr, CL_TRUE, 0,
			sizeof(cl_int) * WIN_WIDTH * WIN_HEIGHT, view->scene, 0, NULL, NULL);
	err = clEnqueueWriteBuffer(cl->queue,cl->bufpts, CL_TRUE, 0,
			sizeof(cl_float) * WIN_WIDTH * WIN_HEIGHT * 2, view->pts, 0, NULL, NULL);
	err = clEnqueueWriteBuffer(cl->queue,cl->bufit, CL_TRUE, 0,
			sizeof(cl_int), view->it, 0, NULL, NULL);
	clFinish(cl->queue);
	err = clSetKernelArg(cl->kernel, 0, sizeof(cl_mem), &cl->bufscr);
	err = clSetKernelArg(cl->kernel, 1, sizeof(cl_mem), &cl->bufpts);
	err = clSetKernelArg(cl->kernel, 2, sizeof(cl_mem), &cl->bufit);
	cl->works = WIN_WIDTH * WIN_HEIGHT;
	err = clEnqueueNDRangeKernel(cl->queue, cl->kernel, 1, NULL, &cl->works, NULL, 0, NULL, NULL);
	err = clEnqueueReadBuffer(cl->queue, cl->bufscr, CL_TRUE, 0, sizeof(cl_int) * WIN_HEIGHT * WIN_WIDTH, view->scene, 0, NULL, NULL);
	clFinish(cl->queue);
	return (cl);
	frac = NULL;
}