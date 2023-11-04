#include "Minirt.h"


double coneIntersectio(t_obj *data, t_cn *cone,t_vector direction, int type)
{
    t_vector origin;
    t_vector cone_normal = normalize(cone->direction);
    if (type == 0)
        origin = data->C->origin;
    else
        origin = data->C->hitpoint;

    t_vector oc  = vector_subtract(origin, cone->origin);
    double m = pow(cone->cone_diam / 2.0, 2) / pow(cone->cone_height, 2);
   // t_vector H = vector_add(cone->origin, multi_vec_by_n(cone_normal, cone->cone_height));
    // printV(H);
    // printV(cone->origin);
   // t_vector w = vector_subtract(origin, H);
  //  t_vector h = normalize(vector_subtract(cone->origin, H));

    double a = dot(direction, direction) - (1 + m) * pow(dot(direction, cone_normal), 2);

    double b = dot(direction, oc) - dot(direction, cone_normal) * \
		dot(oc, cone_normal) * (1 + m) + m * \
		cone->cone_height * dot(direction, cone_normal);
    
    double c = dot(oc, oc) - pow(dot(oc, cone_normal), 2) * \
		(1 + m) - pow(cone->cone_diam/2, 2) + 2 * \
		m * cone->cone_height * dot(oc, cone_normal);

    double delta = pow(b,2) - a *c;
    if(delta < 0)
        return 0;
    double t1 = (-b -sqrt(delta)) /  a; 
    double t2 = (-b +sqrt(delta)) /  a; 
    if (t1 < 0 && t2 < 0)
        return 0;
    if (t1 < 0)
        return t2;
    if (t2 < 0)
        return t1;
    return (fmin(t1 , t2));
}

double getcone(t_obj *data, t_cn *cone, t_vector direction, int type)
{
    double t;
    double d = 0;
    t_vector origin;
    
    t_vector cone_normal = normalize(cone->direction);
    
    if (type == 0)
        origin = data->C->origin;
    else
        origin = data->C->hitpoint;
    //printV(origin);
    t = coneIntersectio(data, cone, direction, type);
    if(t > 0)
    {
        t_vector hitpoint =  vector_add(origin, multi_vec_by_n(direction, t));
        d = dot(vector_subtract(hitpoint , cone->origin) ,cone_normal);
        if(d < 0 || d > cone->cone_height)
           return 0;
        cone->interssection_direction = normalize(vector_subtract(hitpoint, vector_add(cone->origin , multi_vec_by_n (cone_normal, d))));
        return t;
    }
    return 0;
}

double coneBtm(t_obj *data, t_cn *cone, t_vector r, double len, int type)
{
	//t_vector cp;
    t_pl p;


    t_vector origin;

    if (type == 0)
        origin = data->C->origin;
    else
        origin = data->C->hitpoint;

	p.origin = cone->origin;

	p.direction = normalize(multi_vec_by_n(cone->direction, -1));

	double t = plane_intersection(data, &p, r, type);
    (void)len;
    if (t > 0)
	{
         t_vector hitpoint = vector_add(origin, multi_vec_by_n(r, t));
		 double y = vector_len(vector_subtract(hitpoint, cone->origin)) ;
		if (pow(y, 2) > pow(cone->cone_diam / 2.0, 2))
		 	return (0);
        cone->interssection_direction = p.direction;
        return t;
	}
	return (0);

}
double cone_top_btm(t_obj *data, t_cn *cone, t_vector direction, int type)
{
    double cy = -1;
    double btm = -1;
    double result = -1.0;
    t_vector cy_;
    t_vector btm_;

    cy = getcone(data, cone, direction, type);
    cy_ = making_new_vector (cone->interssection_direction.x , cone->interssection_direction.y, cone->interssection_direction.z);
    btm = coneBtm(data, cone, direction, cy, type);
    btm_ = making_new_vector (cone->interssection_direction.x , cone->interssection_direction.y, cone->interssection_direction.z);
    
    if (!cy && !btm)
        return (0);
    result = minPositive(cy, btm, DBL_MAX, DBL_MAX);
    if (result == cy)
    cone->interssection_direction = making_new_vector(cy_.x, cy_.y, cy_.z);
    else if (result == btm)
        cone->interssection_direction = making_new_vector(btm_.x, btm_.y, btm_.z);
    return (result);
}