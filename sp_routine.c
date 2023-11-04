#include "Minirt.h"

double sphere_intersection(t_sp *sp_data, t_vector ray, int type)
{
    double b;
    double c;
    double distance;
    double distance1;
    double distance2;
    t_vector cam_sphere;
    t_vector origin;

    distance1 = 0;
    distance2 = 0;
    if (type == 0)
        origin = sp_data->data->C->origin;
    else
        origin = sp_data->data->C->hitpoint;
    cam_sphere = vector_subtract(origin, sp_data->center);
    double a = dot(ray,ray);
    b = 2 * (dot(ray, cam_sphere));
    c = dot(cam_sphere, cam_sphere) - (sp_data->sphere_diam / 2) * (sp_data->sphere_diam / 2);
    distance = (b * b) - (4 * c * a);
    if (distance < 0)
        return (0);
    distance1 = (-b - sqrt(distance)) / (2 * a);
    distance2 = (-b +  sqrt(distance)) / (2 * a);
    if (distance1 < 0 && distance2 < 0)
        return (0);
    if (distance1 < 0)
        return (distance2);
    if (distance2 < 0)
        return (distance1);
    return (fmin(distance1, distance2));
}

t_vector calculate_ray_direction(t_obj *data, double u, double v)
{
    t_vector scaledUp;
    t_vector scaledRight;
    t_vector ray_direction;

    scaledRight= multi_vec_by_n(data->C->h, u);
    scaledUp= multi_vec_by_n(data->C->v, v);

    ray_direction = normalize(vector_subtract(vector_add(vector_add(data->C->btmlft, scaledUp), scaledRight), data->C->origin));
    return (ray_direction);
}

void my_mlx_pixel_put(t_obj *data,int i,int  j,int color)
{
    char *dst;
    dst = data->vars->addr + (j * data->vars->line_length + i * (data->vars->bits_per_pixel / 8));
    *(int *)dst = color;

}

double shade_intersection(t_obj *data, t_vector ray)
{
    size_t i_sphere = 0;
    size_t i_plane = 0;
    size_t i_cylinder = 0;
    double len_plane= 0.0;
    double len_sphere = 0.0;
    double len_cylinder = 0.0;
    double len_cone = 0.0;
    double result;

    len_plane = plane_global(data, ray, &i_plane, 1);
    len_sphere = sphere_global(data, ray, &i_sphere, 1);
    len_cylinder = cylinder_global(data, ray, &i_cylinder, 1);
    len_cone = cone_top_btm(data, data->cn, ray, 1);
    if (!len_plane && !len_sphere && !len_cylinder && !len_cone)
        return (0.0);
    else
    {
        result = minPositive(len_cone, len_cylinder, len_plane, len_sphere);
        return (result);
    }
}

double shades(t_obj *data, t_vector ray_origin, t_vector normal)
{
    t_vector hit_point;
    data->C->hitpoint = vector_add(ray_origin, multi_vec_by_n(normal, EPS));
    t_vector Z = making_new_vector(data->L->x, data->L->y, data->L->z);
    t_vector ray_direction = vector_subtract(Z, ray_origin);
    double t = vector_len(ray_direction);
    ray_direction = normalize(ray_direction);
    double distance = shade_intersection(data, ray_direction);
    if (distance < 0)
        return (0);
    hit_point = vector_add(data->C->hitpoint, multi_vec_by_n(ray_direction, distance));
	if (distance > 0.0 && t - vector_len(vector_subtract(data->C->hitpoint, hit_point)) > 0)
		return (distance);
	return (0);
}

t_vector reflection(t_vector L, t_vector N)
{
    //R = 2(L.N)N - L
    t_vector R = vector_subtract(multi_vec_by_n(N, 2.0 * dot(L, N)), L);
    return (R);
}

t_vector specular(t_obj *data, t_vector L, t_vector N, t_vector V)
{
    (void)data;
    t_vector R = reflection(L, N);
    // double d = dot(R, V);
    // if (d < 0)
    //     return(making_new_vector(0,0,0));
   // t_vector a = multi_vec_by_n(making_new_vector(data->L->R/255, data->L->G/255, data->L->B/255), data->L->light_ratio * pow(d, 32));
    // t_vector V = normalize(vector_subtract(data->C->origin, N));
   double  d =  pow(fmax(0.0,dot(R,V)),32);
    // a->x *= 255;
    // a->y *= 255;
    // a->z *= 255;
    return multi_vec_by_n(making_new_vector(data->L->R, data->L->G, data->L->B), data->L->light_ratio * d);

    //prdoubleV(a);t
   // return (a);
}

t_vector checkerboard_cylinder(t_vector hitpoint)
{
    t_vector light;
    double constant = 0.2;
    if ((int)((floor(hitpoint.x * constant) + floor(hitpoint.y * constant) )) % 2 == 0)
		light = making_new_vector(102,0,0);
	else
		light = making_new_vector(242,202,92);
    return light;
}
t_vector checkerboard_plane(t_pl *data_pl, t_vector hitpoint)
{
    (void) data_pl;
    t_vector light;
    double constant = 0.1;
    if ((int)((floor(hitpoint.x * constant + EPS) + floor(hitpoint.y * constant + EPS) + floor(hitpoint.z * constant  + EPS))) % 2 == 0)
		light = making_new_vector(0,0,0);
	else
		light = making_new_vector(255,255,255);
    return light;
}

void uv_checker(t_sp *data_sp, double *u, double *v, t_vector hitpoint)
{   
   double x;
   double y;

   x = atan2(hitpoint.x , hitpoint.z) / (2 * M_PI) ; 
   y = acos(hitpoint.y / (data_sp->sphere_diam / 2 ));
   *u = 1.0 - (x + 0.5);
   *v = 1.0 - y / M_PI;
}

t_vector checkerboard_sphere(t_sp *data_sp, t_vector hitpoint)
{
    
    double u = 0;
    double v = 0;
    
    t_vector light; 
    uv_checker(data_sp, &u, &v, hitpoint);
    int x = 16 * u ;
    int y = 8 * v ;
    int checkerboard = 0;
    if (checkerboard )
    {
        if ((x + y) % 2 == 0)
        { 
            light = making_new_vector(0,191,255);
        }
        else
        {

            light = making_new_vector(255,0,0);
        }

    }
    else 
        light = making_new_vector(255,255,255);
    return light ;
}
struct s_vars texture_img;
int ambient_lighting(t_obj *data, t_vector ray, double len, size_t i, int type)
{
    double angle = 0;
    // t_vector BC;
    // t_vector AB;
    t_vector A;
    // t_vector Unit_BC;
    // t_vector E ;
    t_vector EA;
    t_vector Z;
    t_vector bumb_color;
    t_vector AZ;
    t_vector light_diffuse = making_new_vector(0,0,0);
    // int checkerboard = 0;
    // t_vector EA_;
    
    
    

    // t_vector AB_;
    int color;
    static int t = 0;
    // t_vector BC_;
    int texture_bumb = 1; 
    t_vector result;
    t_vector ambient_color = making_new_vector(data->A->R, data->A->G, data->A->B);
    
    if (type == 2)//cylinder
    {
        A = vector_add(data->C->origin, multi_vec_by_n(ray, len));
        Z = making_new_vector(data->L->x, data->L->y, data->L->z);
        AZ = normalize(vector_subtract(Z, A));   
        angle = dot(AZ,data->cy[i]->interssection_direction);
        // if (shades(data, A, data->cy[i]->interssection_direction))
        //     light_diffuse = making_new_vector(0,0,0);
        // else
            light_diffuse = (diffuse_cy(data, angle, A));
    }

    else if (type == 3) // sphere
    {

        A = vector_add(data->C->origin, multi_vec_by_n(ray, len));
        EA = normalize(vector_subtract(A, data->sp[i]->center));
        Z = making_new_vector(data->L->x, data->L->y, data->L->z);
        AZ = normalize(vector_subtract(Z, A));
        angle = dot(AZ, EA);
        if (shades(data, A, AZ))
            light_diffuse = making_new_vector(0,0,0);
        else
        {
            
            light_diffuse = (diffuse_s(data, data->sp[i],angle, A));
            // else 
                // light_diffuse = (diffuse(data, angle));
        }
        if (texture_bumb)
        {   
            if (t == 0) 
            {
                texture_img = loading_texture(data->vars);    
                t = 1;
            }
            bumb_color = get_texture_pixel(texture_img, data->sp[i], A);
        
        }
    }
    else if (type == 1) // plane
    {
        if (dot(data->pl[i]->direction, ray) > 0)
        {
            data->pl[i]->direction =  (multi_vec_by_n(data->pl[i]->direction, -1));
        }
        // printf("%zu\n", i );
        A = vector_add(data->C->origin, multi_vec_by_n(ray, len));
        Z = making_new_vector(data->L->x, data->L->y, data->L->z);
        AZ = normalize(vector_subtract(Z, A));
        angle = dot(AZ, data->pl[i]->direction);

       
        if (shades(data, A, data->pl[i]->direction))
            light_diffuse = making_new_vector(0,0,0);
        else
            light_diffuse = vector_add(diffuse_p(data, data->pl[i],  angle, A), specular(data, AZ, normalize(data->pl[i]->direction), normalize(vector_subtract(data->C->origin, A))));
    }
    else if (type == 4) //cone
    {
        A = vector_add(data->C->origin, multi_vec_by_n(ray, len));
        Z = making_new_vector(data->L->x, data->L->y, data->L->z);
        AZ = normalize(vector_subtract(Z, A));
        angle = dot(AZ, data->cn->interssection_direction);
        // if (shades(data, A, data->cn->interssection_direction))
        //     light_diffuse = making_new_vector(0,0,0);
        // else
        {
            light_diffuse = vector_add(diffuse(data, angle), specular(data, AZ, data->cn->interssection_direction, normalize(vector_subtract(data->C->origin, A))));
        }
    }
    else
    {
        result = multi_vec_by_n(ambient_color, data->A->light_ratio);
        return (set_color(result.x, result.y, result.z));
    }
    t_vector updated_a_c = vector_add(multi_vec_by_n(ambient_color, data->A->light_ratio), light_diffuse);
    t_vector object_color ;
    if (type == 1)
        object_color = making_new_vector(data->pl[i]->R, data->pl[i]->G, data->pl[i]->B);
    else if (type == 2)
        object_color = making_new_vector(light_diffuse.x, light_diffuse.y, light_diffuse.z);
    else if (type == 3)
    {
        if (texture_bumb)
            object_color = making_new_vector(bumb_color.x, bumb_color.y, bumb_color.z);
        else
            object_color = making_new_vector(light_diffuse.x, light_diffuse.y, light_diffuse.z);
    }
    else if (type == 4)
        object_color = making_new_vector(data->cn->R, data->cn->G, data->cn->B);
    updated_a_c.x /= 255.0;
    updated_a_c.y /= 255.0;
    updated_a_c.z /= 255.0;

    
    object_color.x /= 255.0;
    object_color.y /= 255.0;
    object_color.z /= 255.0;
    result = multiple_vec_by_vec(updated_a_c, object_color);

    color = set_color(result.x *255.0 , result.y * 255.0, result.z * 255.0);
    return (color); 
}
