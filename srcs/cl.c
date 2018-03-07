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
#include <fcntl.h>

const char *str = {
		"kernel void mandel(global int *scene, global double *param)"
				"{"
				"	int		id = get_global_id(0);"
				"	double	r, im, rp, p, u;"
				"	double	it;"
				""
				"	p = ((id % (int)(param[6]/4)) - param[2])/(param[1] * 100.0) + param[4];"
				"	u = ((id / (int)(param[6]/4)) - param[3])/(param[1] * 100.0) + param[5];"
				"	r = 0.0;"
				"	it = 0;"
				"	im = 0.0;"
				"	while ((r * r + im * im) < 16.0 && (it++ < param[0]))"
				"	{"
				"		rp =r;"
				"		r = ((r * r) - (im * im) + p);"
				"		im = ((2 * rp * im) + u);"
				"	}"
				"	if (it < param[0])"
				"		scene[id] = ((it / (float)param[0]))* 0xffffff;"
				"	else"
				"		scene[id] = 0xffffff;"
				"}"
};

char	*get_kernel(char *frac)
{
	char	*rslt;
	char	*a;
	char	*b;
	int		fd;
	int		e;

	errno = 0;
	fd = open(frac, O_RDONLY);
	if (errno)
		perror("Fractal not found");
	rslt = NULL;
	a = NULL;
	b = NULL;
	while ((e = get_next_line(fd, &b)) == 1)
	{
		a = rslt;
		rslt = ft_strjoin(a, b);
		free(a);
		free(b);
	}
	close(fd);
	return (rslt);
}

t_cl	*cl_init(t_view *view, char *frac)
{
	t_cl	*cl;
	char	*src;
	int		err;

	cl = (t_cl*)malloc(sizeof(t_cl));

	err = clGetDeviceIDs(NULL, CL_DEVICE_TYPE_GPU, 1, &(cl->device), NULL);
	cl->context = clCreateContext(NULL, 1, &cl->device, NULL, NULL, &err);
	cl->queue = clCreateCommandQueue(cl->context, cl->device, 0, &err);
	cl->bufscr = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
			sizeof(cl_int) * WIN_HEIGHT * WIN_WIDTH, NULL, &err);
	cl->bufparam = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
			sizeof(cl_double) * 9, NULL, &err);
	src = get_kernel(frac);
	cl->program = clCreateProgramWithSource(cl->context, 1, (const char**)&src, NULL, &err);
	err = clBuildProgram(cl->program, 1, &cl->device, NULL, NULL, NULL);
	cl->kernel = clCreateKernel(cl->program, "mandel", &err);
	err = clEnqueueWriteBuffer(cl->queue,cl->bufscr, CL_TRUE, 0,
			sizeof(cl_int) * WIN_WIDTH * WIN_HEIGHT, view->scene, 0, NULL, NULL);
	err = clEnqueueWriteBuffer(cl->queue,cl->bufparam, CL_TRUE, 0,
			sizeof(cl_double) * 9, view->param, 0, NULL, NULL);
	clFinish(cl->queue);
	err = clSetKernelArg(cl->kernel, 0, sizeof(cl_mem), &cl->bufscr);
	err = clSetKernelArg(cl->kernel, 1, sizeof(cl_mem), &cl->bufparam);
	cl->works = WIN_WIDTH * WIN_HEIGHT;
	err = clEnqueueNDRangeKernel(cl->queue, cl->kernel, 1, NULL, &cl->works, NULL, 0, NULL, NULL);
	err = clEnqueueReadBuffer(cl->queue, cl->bufscr, CL_TRUE, 0, sizeof(cl_int) * WIN_HEIGHT * WIN_WIDTH, view->scene, 0, NULL, NULL);
	clFinish(cl->queue);
	return (cl);
	frac = NULL;
}