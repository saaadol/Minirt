#include "Minirt.h"
int	clamp(int c)
{
	if (c > 255)
		c = 255;
	if (c < 0)
		c = 0;
	return (c);
}


int     set_color(int R, int G, int B)
{
    int color = 0;
    void *locate;

    locate = &color;
    ft_memset(locate, clamp(B), 1);
    locate++;
    ft_memset(locate, clamp(G), 1);
    locate++;
    ft_memset(locate, clamp(R), 1);
    return (color);
}

void printV(t_vector v)
{
    printf("x : %f  y  : %f z : %f\n",v.x,v.y,v.z);
   
}

t_obj *calculateBtmLeft(t_obj *data)
{
    data->C->h = multi_vec_by_n(data->C->right, data->C->vpw);
    data->C->v = multi_vec_by_n(data->C->up, data->C->vph);
    data->C->btmlft = vector_subtract(data->C->origin,vector_add(multi_vec_by_n(vector_add(data->C->h,data->C->v),1.0/2.0),data->C->forward));
    return (data);
}

void    setup_camera(t_obj *data)
{
    double aspect_ratio;
    aspect_ratio = Weight / Height;
    t_vector up = making_new_vector(0, 1, 0);
    data->C->origin = making_new_vector(data->C->x, data->C->y, data->C->z);
    data->C->direction = making_new_vector(data->C->x_axis, data->C->y_axis, data->C->z_axis);
    data->C->forward = multi_vec_by_n(normalize(data->C->direction),-1);
    t_vector a, b;
    a = cross(up,data->C->forward);
    data->C->right = normalize(a);
    b = cross(data->C->forward, data->C->right);
   
    data->C->up = normalize(b);
    data->C->vpw = 2.0 * (tan((data->C->FOV * M_PI / 180.0) / 2.0));
    data->C->vph = data->C->vpw / aspect_ratio;
    data = calculateBtmLeft(data);
    //free(up);
    //free(a);
    //free(b);
}

double  sphere_global(t_obj *data, t_vector ray, size_t *i, int shade)
{
    size_t j = 0;
    double len_sphere_next = 0.0;
    double len;
    double  len_sphere = sphere_intersection(data->sp[*i], ray, shade);
    (*i)++;
    while(data->sp[*i])
    {
        len_sphere_next = sphere_intersection(data->sp[*i], ray, shade);
        if (len_sphere_next > 0)
        {
            if (!len_sphere)
            {
                len_sphere = len_sphere_next;
                j = *i;
            }
            else
            {
                len = fmin(len_sphere_next, len_sphere);
                if (len == len_sphere_next)
                {
                    len_sphere = len_sphere_next;
                    j = *i;
                }
            }
        }
        (*i)++;
    }
    (*i) = j;
    return(len_sphere);
}

double  cylinder_global(t_obj *data, t_vector ray, size_t *i, int shade)
{
    size_t j = 0;
    double len_cylinder_next = 0.0;
    double len;
    double  len_cylinder = cy_top_btm(data, data->cy[*i], ray, shade);
    (*i)++;
    while(data->cy[*i])
    {
        len_cylinder_next = cy_top_btm(data, data->cy[*i], ray, shade);
        if (len_cylinder_next > 0)
        {
            if (!len_cylinder)
            {
                len_cylinder = len_cylinder_next;
                j = *i;
            }
            else
            {
                len = fmin(len_cylinder_next, len_cylinder);
                if (len == len_cylinder_next)
                {
                    len_cylinder = len_cylinder_next;
                    j = *i;
                }
            }
        }
        (*i)++;
    }
    (*i) = j;
    return(len_cylinder);
}

double  plane_global(t_obj *data, t_vector ray, size_t *i, int shade)
{
    size_t j = 0;
    double len_plane_next = 0.0;
    double len;
    double  len_plane = plane_intersection(data, data->pl[*i], ray, shade);
    (*i)++;
    while(data->pl[*i])
    {
        len_plane_next = plane_intersection(data, data->pl[*i], ray, shade);
        if (len_plane_next > 0)
        {
            if (!len_plane)
            {
                len_plane = len_plane_next;
                j = *i;
            }
            else
            {
                len = fmin(len_plane_next, len_plane);
                if (len == len_plane_next)
                {
                    len_plane = len_plane_next;
                    j = *i;
                }
            }
        }
        (*i)++;
    }
    (*i) = j;
    return(len_plane);
}

double minPositive(double a, double b, double c, double d)
{
    double min = DBL_MAX;

    if (a > 0.0 && a < min) {
        min = a;
    }
    if (b > 0.0 && b < min) {
        min = b;
    }
    if (c > 0.0 && c < min) {
        min = c;
    }
    if (d > 0.0 && d < min) {
        min = d;
    }

    if (min == DBL_MAX) {
        return 0.0;
    }
    return min;
}


int intersection(t_obj *data, t_vector ray, int *color)
{
    size_t i_sphere = 0;
    size_t i_cylinder = 0;
    size_t i_plane = 0;
    size_t i_cone = 0;
    double len_plane= 0.0;
    double len_sphere = 0.0;
    double len_cylinder = 0.0;
    double len_cone = 0.0;
    double result;

    len_plane = plane_global(data, ray, &i_plane, 0);
    len_sphere = sphere_global(data, ray, &i_sphere, 0);
    len_cylinder = cylinder_global(data, ray, &i_cylinder, 0);
    len_cone = cone_top_btm(data, data->cn, ray, 0);
    if (!len_plane && !len_sphere && !len_cylinder && !len_cone)
    {
        (*color) = ambient_lighting(data, ray, 0, 0, 0);
        return (1);
    }
    else
    {
        result = minPositive(len_cone, len_cylinder, len_plane, len_sphere);
        if (result == len_plane)    
            *color = ambient_lighting(data, ray, len_plane, i_plane, 1);
        else if (result == len_cylinder)
            *color = ambient_lighting(data, ray, len_cylinder, i_cylinder, 2);
        else if (result == len_sphere)
            *color = ambient_lighting(data, ray, len_sphere, i_sphere, 3);
        else if (result == len_cone)
            *color = ambient_lighting(data, ray, len_cone, i_cone, 4);
        return (1);
    }
}

void    ray_tracer(t_obj *data)
{
    t_vector ray;
    double i;
    double j;
    double u;
    double v;
    int color;
   
    j = Height -1;
    u = 0;
    v = 0;
    while(j >= 0)
    {
        i = 0;
        while(i <= Weight - 1.0)
        {
            u = (i / ((double) Weight - 1.0));
            v = (j / ((double) Height - 1.0));
            ray = calculate_ray_direction(data, u, v);
            if (intersection(data, ray, &color))
                my_mlx_pixel_put(data ,(int)i, Height - (int)j - 1, color);
            i++;
        }
        j--;
    }
}

void    drawing_func(t_obj *data)
{
    setup_camera(data);
    ray_tracer(data);
    mlx_put_image_to_window(data->vars->mlx, data->vars->win, data->vars->img, 0, 0);
    return;
}