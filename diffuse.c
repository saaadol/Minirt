#include "Minirt.h"

t_vector diffuse(t_obj *data, double angle)
{
    t_vector light;
    t_vector diffuse;
   
    light =  making_new_vector(data->L->x, data->L->y, data->L->z);
    if (angle > 0)
        diffuse = multi_vec_by_n(light, data->L->light_ratio * angle * 0.5);
    else
        diffuse = making_new_vector(0, 0, 0);
    return(diffuse);
}
t_vector diffuse_p(t_obj *data,t_pl *data_pl, double angle,t_vector A)
{
    t_vector light;
    t_vector diffuse;

    light =  checkerboard_plane(data_pl, A);
    
    if (angle > 0)
        diffuse = multi_vec_by_n(light, data->L->light_ratio * angle * 0.5);
    else
        diffuse = making_new_vector(0, 0, 0);

    return(diffuse);
}
t_vector diffuse_cy(t_obj *data, double angle,t_vector A)
{
    t_vector light;
    t_vector diffuse;
   
    light =  checkerboard_cylinder(A);
    if (angle > 0)
        diffuse = multi_vec_by_n(light, data->L->light_ratio * angle * 0.5);
    else
        diffuse = making_new_vector(0, 0, 0);
    return(diffuse);
}

t_vector diffuse_s(t_obj *data,t_sp *data_sp, double angle, t_vector hitpoint)
{
    t_vector light;
    t_vector diffuse;
    
    light =  checkerboard_sphere(data_sp, hitpoint);
    if (angle > 0)
        diffuse = multi_vec_by_n(light, data->L->light_ratio * angle * 0.5);
    else
        diffuse = making_new_vector(0, 0, 0);
    return(diffuse);
}


t_vector checkerboard_cone(t_vector hitpoint)
{
    // double u;
    // double v;
    t_vector light;
    // uv_checker_cone(&u, &v, hitpoint);
    // printf("%f - %f\n", u,v);
    //  int x = u * 2;
    // int y = v * 2; 
    if ((int)((floor(hitpoint.x * 0.1 ) + floor(hitpoint.y * 0.1 ) + floor(hitpoint.z * 0.1  ))) % 2 == 0)
    {

		light = making_new_vector(255,255,255);
    }
	else
    {
		light = making_new_vector(255,0,0);
    }
    return light;
}
