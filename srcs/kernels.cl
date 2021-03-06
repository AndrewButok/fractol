int         get_color(float it, float itm, float color)
{
	if (((int)color) == 0xffffff)
		return (int)(it/itm * (int)color);
	else if (((int)color) == 0xff0000)
		return ((int)(it/itm * 0xff))<<16;
	else if (((int)color) == 0xff00)
    	return ((int)(it/itm * 0xff))<<8;
    else if (((int)color) == 0xff)
    	return ((int)(it/itm * 0xff));
    else if (((int)color) == 0xffff00)
    	return (((int)(it/itm * 0xff))<<8) | (((int)(it/itm * 0xff))<<16);
    else
        return ((int)(it/itm * 0xff)) | (((int)(it/itm * 0xff))<<8) | (((int)(it/itm * 0xff))<<16);
}

kernel void Mandelbrot(global int *scene, global float *param)
{
	int		id = get_global_id(0);
	float	r, im, rp, p, u;
	float	it;

    p = ((id % (int)(param[6]/4)) - param[2])/(param[1] * 100) + param[4];
    u = ((id / (int)(param[6]/4)) - param[3])/(param[1] * 100) + param[5];
	r = 0;
	it = 0;
	im = 0;
	while ((r * r + im * im) < 16 && (it++ < param[0]))
	{
		rp = r;
		r = (r * r) - (im * im) + p;
		im = (2 * rp * im) + u;
	}
	if (it < param[0])
		scene[id] = get_color(it, param[0], param[9]);
	else
		scene[id] = 0xffffff;
}

kernel void Julia(global int *scene, global float *param)
{
	int		id = get_global_id(0);
	float	r, im, rp, p, u;
	float	it;

	r = ((id % (int)(param[6]/4)) - param[2])/(param[1] * 100) + param[4];
    im = ((id / (int)(param[6]/4)) - param[3])/(param[1] * 100) + param[5];
    p = (param[7] - param[2])/(100);
    u = (param[8] - param[3])/(100);
	it = 0;
	while ((r * r + im * im) < 16 && (it++ < param[0]))
	{
		rp = r;
		r = (r * r) - (im * im) + p;
		im = (2 * rp * im) + u;
	}
	if (it < param[0])
		scene[id] = get_color(it, param[0], param[9]);
	else
		scene[id] = 0xffffff;
}

kernel void Burningship(global int *scene, global float *param)
{
	int		id = get_global_id(0);
	float	r, im, rp, p, u;
	float	it;

	p = ((id % (int)(param[6]/4)) - param[2])/(param[1] * 100) + param[4];
u = ((id / (int)(param[6]/4)) - param[3])/(param[1] * 100) + param[5];
	r = 0;
	it = 0;
	im = 0;
	while ((r * r + im * im) < 16 && (it++ < param[0]))
	{
		rp = r;
		r = fabs((r * r) - (im * im) + p);
		im = fabs((2 * rp * im) + u);
	}
	if (it < param[0])
		scene[id] = get_color(it, param[0], param[9]);
	else
		scene[id] = 0xffffff;
}

kernel void Interstellar(global int *scene, global float *param)
{
	int		id = get_global_id(0);
	float	r, im, rp, p, u;
	float	it;

	p = ((id % (int)(param[6]/4)) - param[2])/(param[1] * 100) + param[4];
	u = ((id / (int)(param[6]/4)) - param[3])/(param[1] * 100) + param[5];
	r = 0;
	it = 0;
	im = 0;
	while ((r * r + im * im) < 16 && (it++ < param[0]))
	{
		rp = r;
		r = tan(fabs(r + p));
		im = tan(fabs(im + u));
	}
	if (it < param[0])
		scene[id] = get_color(it, param[0], param[9]);
	else
		scene[id] = 0xffffff;
}

kernel void Butterfly(global int *scene, global float *param)
{
	int		id = get_global_id(0);
	float	r, im, rp, p, u;
	float	it;

	p = ((id % (int)(param[6]/4)) - param[2])/(param[1] * 100) + param[4];
    u = ((id / (int)(param[6]/4)) - param[3])/(param[1] * 100) + param[5];
	r = 0;
	it = 0;
	im = 0;
	while ((r * r + im * im) < 16 && (it++ < param[0]))
	{
		rp = r;
		r = tanh(r + p)/tanh(im + u) * sin(p) + p + r;
		im = tanh(im + u)/tanh(rp + p) * sin(u) + u +im;
	}
	if (it < param[0])
		scene[id] = get_color(it, param[0], param[9]);
	else
		scene[id] = (int)param[9];
}

kernel void Mandelbrot3(global int *scene, global float *param)
{
	int		id = get_global_id(0);
	float	r, im, rp, p, u;
	float	it;

	p = ((id % (int)(param[6]/4)) - param[2])/(param[1] * 100) + param[4];
                u = ((id / (int)(param[6]/4)) - param[3])/(param[1] * 100) + param[5];
	r = 0;
	it = 0;
	im = 0;
	while ((r * r + im * im) < 16 && (it++ < param[0]))
	{
		rp = r;
		r = r*r*r - 3*r*im*im + p;
                    im = 3*r*r*im - 3*im*im*im + u;
	}
	if (it < param[0])
		scene[id] = get_color(it, param[0], param[9]);
	else
		scene[id] = 0xffffff;
}

kernel void FabsJulia(global int *scene, global float *param)
{
	int		id = get_global_id(0);
    float	r, im, rp, p, u;
    float	it;

    r = ((id % (int)(param[6]/4)) - param[2])/(param[1] * 100) + param[4];
    im = ((id / (int)(param[6]/4)) - param[3])/(param[1] * 100) + param[5];
    p = (param[7] - param[2])/(100);
    u = (param[8] - param[3])/(100);
    it = 0;
    while ((r * r + im * im) < 16 && (it++ < param[0]))
    {
    	rp = r;
    	r = fabs(((r * r) - (im * im)) - p);
    	im = fabs(((2 * rp * im)) - u);
    }
    if (it < param[0])
    	scene[id] = get_color(it, param[0], param[9]);
    else
    	scene[id] = 0xffffff;
}

kernel void Newton(global int *scene, global float *param)
{
	int		id = get_global_id(0);
	float	r, im, rp, ip, p, u, c;
	float	it;

	r = ((id % (int)(param[6]/4)) - param[2])/(param[1] * 100) + param[4];
    im = ((id / (int)(param[6]/4)) - param[3])/(param[1] * 100) + param[5];
    p = r;
    u = im;
	it = 0;
	while ((r * r + im * im) < 100000000 && p*p + u*u > 0.0000000001f && (it++ < param[0]))
	{
		rp = r;
		ip = im;
		c = pow(pow(rp, 2) + pow(ip, 2), 2);
		r = 2/3.0f * r + (pow(rp, 2) - pow(im, 2))/(3*c);
		im = 2/3.0f * im * (1 - rp / c);
		p = fabs(r - rp);
		u = fabs(im - ip);

	}
	if (it < param[0])
		scene[id] = get_color(it, param[0], param[9]);
	else
		scene[id] = 0xffffff;
}
