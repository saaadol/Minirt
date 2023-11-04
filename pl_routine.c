#include "Minirt.h"

double plane_intersection(t_obj *data, t_pl *p, t_vector ray, int type)
{
	t_vector plane_direction;
	t_vector cam_plane;
	t_vector origin;
	double	t;
	double	distance1;
	double	distance2;

	if (type == 0)
		origin = data->C->origin;
	else
		origin = data->C->hitpoint;
	cam_plane = vector_subtract(origin, p->origin);
	plane_direction = normalize(p->direction);
	t = dot(ray, plane_direction);
	if (t != 0)
	{
		distance1 = dot(cam_plane, plane_direction);
		distance2 = -distance1 / t;
		if (distance2 < EPS)
			return (0);
		return (distance2);
	}
	return (0);
}
