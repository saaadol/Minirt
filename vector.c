#include "Minirt.h"

t_vector     making_new_vector(double x, double y, double z)
{
    t_vector vector;

    vector.x = x;
    vector.y = y;
    vector.z = z;
    return (vector);
}

t_vector    vector_subtract(t_vector v1, t_vector v2)
{
    t_vector substract;
    double   delta_x;
    double   delta_y;
    double   delta_z;

    delta_x = v1.x - v2.x;
    delta_y = v1.y - v2.y;
    delta_z = v1.z - v2.z;
    substract = making_new_vector(delta_x, delta_y, delta_z);
    return (substract);
}

t_vector vector_add(t_vector v1, t_vector v2)
{
    t_vector substract;
    double   delta_x;
    double   delta_y;
    double   delta_z;

    delta_x = v1.x + v2.x;
    delta_y = v1.y + v2.y;
    delta_z = v1.z + v2.z;
    substract = making_new_vector(delta_x, delta_y, delta_z);
    return (substract);
}

double   vector_len(t_vector vector)
{
    double len;

    len = sqrt((vector.x * vector.x) + (vector.y * vector.y) + (vector.z * vector.z));
    return (len);
}

t_vector  normalize(t_vector vector)
{
    double len;

    len = vector_len(vector);
    if (len > 0)
    {
        vector.x = vector.x / len;
        vector.y = vector.y / len;
        vector.z = vector.z / len;
    }
    return (vector);
}

t_vector multi_vec_by_n(t_vector vec, double n)
{
    t_vector vector = making_new_vector(vec.x * n, vec.y * n, vec.z * n);
	return (vector);
}


t_vector cross(t_vector v1, t_vector v2)
{
    t_vector vector;

    vector = making_new_vector(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
    return (vector);
}

t_vector multiple_vec_by_vec(t_vector v1, t_vector v2)
{
    t_vector vector;

    vector = making_new_vector((v1.x * v2.x) , (v1.y * v2.y) , (v1.z * v2.z));
    return (vector);
}

double dot(t_vector v1, t_vector v2)
{
    double distance;

    distance = ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
    return (distance);
}