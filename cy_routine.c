#include "Minirt.h"


double cylinderIntersectio(t_obj *data, t_cy *cy_data,t_vector direction, int type)
{
    t_vector origin;

    if (type == 0)
        origin = data->C->origin;
    else
        origin = data->C->hitpoint;

    cy_data->bottom_vector = vector_add(cy_data->origin, multi_vec_by_n(normalize(cy_data->direction), - (cy_data->cylinder_height / 2)));
    t_vector w = vector_subtract(origin, cy_data->bottom_vector);
    double a ,b,c;
    a = dot(direction,direction) - pow(dot (direction,normalize(cy_data->direction)),2);
    b = 2 * (dot(direction , w) - (dot(direction, normalize(cy_data->direction))* dot(w,normalize(cy_data->direction))));
    c = dot(w,w) - pow(dot(w,normalize(cy_data->direction)),2) - pow(cy_data->cylinder_diam/2, 2);
    double delta = pow(b,2) - (4*a*c);
    if(delta < 0)
        return -1;
    double t1 = (-b - sqrt(delta)) /(2 * a);
    double t2 = (-b + sqrt(delta)) /(2 * a);

    if(t1 < 0 && t2 < 0)
        return -1;
    if(t1 < 0)
        return t2;
    if(t2 < 0)
        return t1;
    return (fmin(t1,t2));
}

double getCylinder(t_obj *data, t_cy *cy_data, t_vector direction, int type)
{
    double t;
    double d = 0;
    t_vector origin;
    cy_data->direction = normalize(cy_data->direction);
    if (type == 0)
        origin = data->C->origin;
    else
        origin = data->C->hitpoint;
    t = cylinderIntersectio(data, cy_data, direction, type);
    if(t > 0)
    {
        t_vector hitpoint =  vector_add(origin, multi_vec_by_n(direction, t));
        d = dot(normalize(cy_data->direction),vector_subtract(hitpoint, cy_data->bottom_vector));
        if(d < 0 || d > cy_data->cylinder_height)
            return 0;
        cy_data->interssection_direction = normalize(vector_subtract(vector_subtract(hitpoint, cy_data->origin), multi_vec_by_n(cy_data->direction, dot(vector_subtract(hitpoint, cy_data->origin), cy_data->direction))));
        return t;
    }
    return 0;
}

double cylinderTop(t_obj *data, t_cy *cy_data, t_vector direction, double len, int type)
{
    t_vector origin;

    if (type == 0)
        origin = data->C->origin;
    else
        origin = data->C->hitpoint;
    double t;
    (void)len;
    cy_data->upper_vector = vector_add(cy_data->origin, multi_vec_by_n(normalize(cy_data->direction), cy_data->cylinder_height / 2));
    t_pl p;
 
    p.origin = making_new_vector(cy_data->upper_vector.x, cy_data->upper_vector.y, cy_data->upper_vector.z);
    p.direction = normalize(making_new_vector(cy_data->direction.x, cy_data->direction.y, cy_data->direction.z));

    t = plane_intersection(data,&p,direction, type);
    if (t > 0)
    {
        t_vector  hitPoint =  vector_add(origin, multi_vec_by_n(direction, t));
        if (vector_len(vector_subtract(hitPoint ,cy_data->upper_vector)) > cy_data->cylinder_diam / 2.0)
                return 0;
        cy_data->interssection_direction = making_new_vector(p.direction.x, p.direction.y, p.direction.z);
        return t;
    }
    return 0;
}

double cylinderBtm(t_obj *data, t_cy *cy_data, t_vector direction, double len, int type)
{
    t_vector origin;

    if (type == 0)
        origin = data->C->origin;
    else
        origin = data->C->hitpoint;
    double t;
    (void)len;
    t_pl p;
    p.origin = making_new_vector(cy_data->bottom_vector.x, cy_data->bottom_vector.y, cy_data->bottom_vector.z);
    p.direction = multi_vec_by_n(normalize(making_new_vector(cy_data->direction.x, cy_data->direction.y, cy_data->direction.z)) , (-1));
    t = plane_intersection(data, &p,direction, type);
    if(t > 0)
    {
        t_vector  hitPoint =  vector_add(origin, multi_vec_by_n(direction, t));
        double area = pow(vector_len(vector_subtract(hitPoint ,cy_data->bottom_vector)),2);
        if (area >= pow(cy_data->cylinder_diam / 2.0,2))
            return 0;
        cy_data->interssection_direction = making_new_vector(p.direction.x, p.direction.y, p.direction.z);
        return t;
    }
    return 0;

}
double cy_top_btm(t_obj *data, t_cy *cy_data, t_vector direction, int type)
{
    double cy = -1,top =-1,btm = -1;
    double result = -1.0;
    t_vector cy_;
    t_vector top_;
    t_vector btm_;

    cy = getCylinder(data, cy_data, direction, type);
    cy_ = making_new_vector (cy_data->interssection_direction.x , cy_data->interssection_direction.y, cy_data->interssection_direction.z);
    top = cylinderTop(data, cy_data, direction, cy, type);
    top_ = making_new_vector (cy_data->interssection_direction.x , cy_data->interssection_direction.y, cy_data->interssection_direction.z);
    btm = cylinderBtm(data, cy_data, direction, top, type);
    btm_ = making_new_vector (cy_data->interssection_direction.x , cy_data->interssection_direction.y, cy_data->interssection_direction.z);
    
    if (cy <= 0 && top <= 0 && btm <= 0)
    {
        result = 0;
        return (result);
    }
    if (cy <= 0)
    {
        result = fmin(top, btm);
        if (result <= 0)
            result = fmax(top, btm);
    }
    else if (top <= 0)
    {
        result = fmin(cy, btm);
        if (result <= 0)
            result = fmax(cy, btm);
    }
    else if (btm <= 0)
    {
        result = fmin(cy, top);
        if (result <= 0)
            result = fmax(cy, top);
    }
    else
        result = fmin(fmin(cy, top), btm);
    if (result == cy)
        cy_data->interssection_direction = making_new_vector(cy_.x, cy_.y, cy_.z);
    else if (result == top)
        cy_data->interssection_direction = making_new_vector(top_.x, top_.y, top_.z);
    else if (result == btm)
        cy_data->interssection_direction = making_new_vector(btm_.x, btm_.y, btm_.z);
    return (result);
}