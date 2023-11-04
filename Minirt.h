#ifndef MINIRT_H
# define MINIRT_H
# define BUFFER_SIZE 42
# define Height 1024
# define Weight 1024
# define EPS 1e-6
# define Projet_name "MiniRT"

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <signal.h>
# include <mlx.h>
#include <float.h>
# include <pthread.h>
# include <math.h>
typedef	struct save_file
{
	char *line;
	struct save_file *next;
}t_save;

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}t_vector ;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		projection;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}t_vars;

typedef struct ambient_lightning
{
	double		R;
	double		G;
	double		B;
	int		color;
	double	light_ratio;
	struct	object *data;	
}t_a;

typedef struct camera
{
	t_vector hitpoint;
	t_vector origin;
	t_vector direction;
	double	x; //coordinate point of view
	double	y; //coordinate point of view
	double	z; //cordinate point of view
	double	x_axis; //3d normalized orientation vector
	double	y_axis; //3d normalized orientation vector
	double	z_axis; //3d normalized orientation vector
	double	FOV; //Horizontal field of view in degrees
	//scene
	t_vector up;
    t_vector forward;
    t_vector right;
    double vph;
    double vpw;
	t_vector h;
	t_vector v;
    t_vector btmlft;
	struct	object *data;
}t_c;

typedef struct light
{
	double	x;
	double	y;
	double	z;
	double	light_ratio;
	double		R;
	double		G;
	double		B;
	int		color;
	struct	object *data;	
}t_l;

typedef	struct vplane
{
	double width;
	double hight;
	double x_pixel;
	double y_pixel;

}t_vplane;


typedef struct sphere
{
	t_vector center;
	double	x;
	double	y;
	double	z;
	double	sphere_diam;
	double		R;
	double		G;
	double		B;
	int		color;
	t_vector hitpoint;
	t_vector interssection_direction;
	struct	object *data;
}t_sp;

typedef struct plane
{
	double	x;
	double	y;
	double	z;
	double	x_axis;
	double	y_axis;
	double	z_axis;
	double		R;
	double		G;
	double		B;
	int		color;
	t_vector origin;
	t_vector hitpoint;
	t_vector direction;
	t_vector interssection_direction;
	struct	object *data;	
}t_pl;

typedef struct cylinder
{
	double	x;
	double	y;
	double	z;
	double	x_axis;
	double	y_axis;
	double	z_axis;
	t_vector hitpoint;
	t_vector origin;
	t_vector direction;
	t_vector bottom_vector;
	t_vector upper_vector;
	double	cylinder_diam;
	double	cylinder_height;
	double		R;
	double		G;
	double		B;
	int		color;
	t_vector interssection_direction; 
	t_vector inte_normal;
	struct	object *data;	
}t_cy;

typedef struct cone
{
	double	x;
	double	y;
	double	z;
	double	x_axis;
	double	y_axis;
	double	z_axis;
	t_vector hitpoint;
	t_vector origin;
	t_vector direction;
	t_vector bottom_vector;
	t_vector upper_vector;
	double	cone_diam;
	double	cone_height;
	double		R;
	double		G;
	double		B;
	int		color;
	t_vector interssection_direction; 
	t_vector inte_normal;
	struct	object *data;	
}t_cn;

typedef struct object
{
	struct s_vars *vars;
	struct ambient_lightning *A;
	struct camera *C;
	struct light *L;
	struct sphere **sp;
	struct plane **pl;
	struct cylinder **cy;
	struct cone *cn;
}t_obj;

void draw_sphere(t_sp **sp_data);
int	parssing(char *file, t_obj *data);
size_t ft_strlen(char *str);
t_vector multi_vec_by_n(t_vector vec, double n);
t_vector cross(t_vector v1, t_vector v2);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int type_check(char *file);
int	ft_strchr(char *s, int c);
void  draw_plane(t_pl **pl_data);
char	*ft_reading_to_stock(int fd, char *stock);
char	*ft_liner(char *stock);
char	*ft_stockage(char *stock);
char	*get_next_line(int fd);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strdup(char *src);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strtrim(char *s1, char *set);
char	**ft_split(char const *s, char c);
t_vector diffuse(t_obj *data, double angle);
t_vector diffuse_p(t_obj *data,t_pl *data_pl, double angle,t_vector A);
int		ft_atoi(char *str);
void    drawing_func(t_obj *data);
void my_mlx_pixel_put(t_obj *data,int i,int  j,int color);
t_vector calculate_ray_direction(t_obj *data, double u, double v);
void	exec_part(t_obj *data);
void *pl_routine(void *param);
void *cy_routine(void *param);
void *L_routine(void *param);
void *sp_routine(void *param);
void *A_routine(void *param);
void *C_routine(void *param);
int ambient_lighting(t_obj *data, t_vector ray, double len, size_t i, int type);
void	*ft_memset(void *b, int c, size_t len);
int     set_color(int R, int G, int B);
t_vector multiple_vec_by_vec(t_vector v1, t_vector v2);
t_vector making_new_vector(double x, double y, double z);
t_vector vector_subtract(t_vector v1, t_vector v2);
double   vector_len(t_vector vector);
t_vector normalize(t_vector vector);
double dot(t_vector v1, t_vector v2);
t_vector vector_add(t_vector v1, t_vector v2);
void printV(t_vector v);
t_vector help(t_vector r);
void  draw_cylinder(t_cy **pl_data);
double cylinder_intersection(t_obj *data, t_vector ray, int type);
double plane_intersection(t_obj *data, t_pl *p, t_vector ray, int type);
double sphere_intersection(t_sp *sp_data, t_vector ray, int type);
void ray_tracing_cylinder(t_cy *pl_data);
void  draw_cylinder(t_cy **pl_data);
double cylinderIntersectio(t_obj *data, t_cy *cy_data, t_vector direction, int type);
double getCylinder(t_obj *data, t_cy *cy_data, t_vector direction, int type);
double cy_top_btm(t_obj *data, t_cy *cy_data, t_vector direction, int type);
double  sphere_global(t_obj *data, t_vector ray, size_t *i, int shade);
double  plane_global(t_obj *data, t_vector ray, size_t *i, int shade);
double  cylinder_global(t_obj *data, t_vector ray, size_t *i, int shade);
t_vector checkerboard_plane(t_pl *data_pl, t_vector hitpoint);

double minPositive(double a, double b, double c, double d);
double cone_top_btm(t_obj *data, t_cn *cy_data, t_vector direction, int type);
t_vector checkerboard_cylinder(t_vector hitpoint);
t_vector diffuse_cy(t_obj *data, double angle,t_vector A);
t_vector checkerboard_sphere(t_sp *data_sp, t_vector hitpoint);
void uv_checker(t_sp *data_sp, double *u, double *v, t_vector hitpoint);
t_vector diffuse_s(t_obj *data, t_sp *data_sp, double angle, t_vector hitpoint);
t_vector diffuse_cn(t_obj *data, double angle,t_vector A);
t_vector checkerboard_cone(t_vector hitpoint);
struct s_vars loading_texture(struct s_vars *data);
t_vector get_texture_pixel(struct s_vars texture, t_sp *sp_data, t_vector hitpoint);
#endif