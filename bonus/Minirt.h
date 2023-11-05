/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souledla <souledla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 13:13:47 by markik            #+#    #+#             */
/*   Updated: 2023/11/05 19:17:59 by souledla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <signal.h>
# include <mlx.h>
# include <limits.h>
# include <pthread.h>
# include <math.h>
# define BUFFER_SIZE 42
# define HIGHT 1024
# define WIDHT 1024
# define EPS 1e-6
# define PROJET_NAME "MiniRT"

typedef struct save_file
{
	char				*line;
	struct save_file	*next;
}t_save;

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}t_vector;

typedef struct s_vars
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				projection;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				width;
	int				hight;
	struct object	*data;
}t_vars;

typedef struct ambient_lightning
{
	double			r;
	double			g;
	double			b;
	int				color;
	double			light_ratio;
	struct object	*data;	
}t_a;

typedef struct camera
{
	t_vector		hitpoint;
	t_vector		origin;
	t_vector		direction;
	double			x;
	double			y;
	double			z;
	double			x_axis;
	double			y_axis;
	double			z_axis;
	double			fov;
	t_vector		up;
	t_vector		forward;
	t_vector		right;
	double			vph;
	double			vpw;
	t_vector		h;
	t_vector		v;
	t_vector		btmlft;
	struct object	*data;
}t_c;

typedef struct light
{
	double			x;
	double			y;
	double			z;
	double			light_ratio;
	double			r;
	double			g;
	double			b;
	int				color;
	struct object	*data;	
}t_l;

typedef struct sphere
{
	struct s_vars	vars;
	t_vector		center;
	double			x;
	double			y;
	double			z;
	double			sphere_diam;
	double			r;
	double			g;
	double			b;
	int				color;
	t_vector		hitpoint;
	t_vector		interssection_direction;
	struct object	*data;
	int				has_bumb;
}t_sp;

typedef struct plane
{
	double			x;
	double			y;
	double			z;
	double			x_axis;
	double			y_axis;
	double			z_axis;
	double			r;
	double			g;
	double			b;
	int				color;
	t_vector		origin;
	t_vector		hitpoint;
	t_vector		direction;
	t_vector		interssection_direction;
	struct object	*data;	
}t_pl;

typedef struct cylinder
{
	double			x;
	double			y;
	double			z;
	double			x_axis;
	double			y_axis;
	double			z_axis;
	t_vector		hitpoint;
	t_vector		origin;
	t_vector		direction;
	t_vector		bottom_vector;
	t_vector		upper_vector;
	double			cylinder_diam;
	double			cylinder_height;
	double			r;
	double			g;
	double			b;
	int				color;
	t_vector		interssection_direction; 
	t_vector		inte_normal;
	struct object	*data;	
}t_cy;

typedef struct cone
{
	t_vector		hitpoint;
	t_vector		origin;
	t_vector		direction;
	t_vector		bottom_vector;
	t_vector		upper_vector;
	t_vector		interssection_direction; 
	t_vector		inte_normal;
	double			x;
	double			y;
	double			z;
	double			x_axis;
	double			y_axis;
	double			z_axis;
	double			cone_diam;
	double			cone_height;
	double			r;
	double			g;
	double			b;
	int				color;
	struct object	*data;
}t_cn;

typedef struct object
{
	struct s_vars				*vars;
	struct cone					*cn;
	struct ambient_lightning	*a;
	struct camera				*c;
	struct light				**l;
	struct sphere				**sp;
	struct plane				**pl;
	struct cylinder				**cy;
	int							checkboard;
}t_obj;

typedef struct intersection_abc
{
	double	i;
	double	j;
	double	u;
	double	v;
	double	m;
	double	a;
	double	b;
	double	c;
	double	delta;
	double	t1;
	double	t2;
}t_mabc;

typedef struct intersection_normal
{
	t_vector		cy;
	t_vector		btm;
	t_vector		top;
	size_t			i_sphere;
	size_t			i_plane;
	size_t			i_cylinder;
	size_t			i_cone;
	size_t			i_light;
	double			len_sphere;
	double			len_plane;
	double			len_cylinder;
	double			len_cone;
	struct object	*data;
}t_cyin;

t_vars		loading_texture(char *file);
t_vector	diffuse(t_obj *data, double angle, t_cyin in);
t_vector	calculate_ray_direction(t_obj *data, double u, double v);
t_vector	result_base_on_type(t_obj *data, t_vector l_d, t_cyin in, int type);
t_vector	get_up(t_vector forward);
t_vector	reflection(t_vector l, t_vector n);
t_vector	specular(t_vector l, t_vector n, t_vector v, t_cyin i);
t_vector	cylinder_lighting(t_obj *data, t_vector ray, t_cyin in);
t_vector	sphere_lighting(t_obj *data, t_vector ray, t_cyin in);
t_vector	plane_lighting(t_obj *data, t_vector ray, t_cyin in);
t_vector	cone_lighting(t_obj *data, t_vector ray, t_cyin in);
t_vector	making_new_vector(double x, double y, double z);
t_vector	vector_subtract(t_vector v1, t_vector v2);
t_vector	vector_add(t_vector v1, t_vector v2);
t_vector	normalize(t_vector vector);
t_vector	multi_vec_by_n(t_vector vec, double n);
t_vector	cross(t_vector v1, t_vector v2);
t_vector	checkerboard_cylinder(t_vector hitpoint, t_cy *cy_data);
t_vector	diffuse_cy(t_obj *data, double angle, t_cyin in, t_vector hitpoint);
t_vector	multiple_vec_by_vec(t_vector v1, t_vector v2);
t_vector	diffuse_pl(t_obj *data, double angle, t_cyin in, t_vector hitpoint);
t_vector	checkerboard_plane(t_vector hitpoint, t_pl *pl_data);
t_vector	diffuse_sp(t_obj *data, double angle, t_cyin in, t_vector hitpoint);
t_vector	checkerboard_sphere(t_vector hitpoint, t_sp *sp_data, t_obj *data);
t_vector	rgb_conversion(int color);
t_vector	get_texture_pixel(struct s_vars texture, \
	t_sp *sp_data, t_vector hitpoint);
t_vector	lighting_type(t_obj *data, t_vector ray, t_cyin in, int type);
double		getcylinder(t_obj *data, t_cy *y, t_vector direction, int type);
double		cylindertop(t_obj *data, t_cy *y, t_vector r_y, int type);
double		cylinderbtm(t_obj *data, t_cy *y, t_vector r_y, int type);
double		cy_top_btm(t_obj *data, t_cy *y, t_vector direction, int type);
double		cylinderintersectio(t_obj *data, t_cy *y, t_vector d, int type);
double		cy_len(double l_cy, double l_cy_next, size_t *j, size_t *i);
double		cylinder_global(t_obj *data, t_vector ray, size_t *i, int shade);
double		vector_len(t_vector vector);
double		minpositive(double a, double b, double c, double d);
double		num_atof(int flag, int i, double num);
double		ft_atof(char *str);
double		shade_intersection(t_obj *data, t_vector ray);
double		shades(t_obj *data, t_vector ray_origin, t_vector normal, size_t i);
double		sphere_intersection(t_sp *sp_data, t_vector ray, int type);
double		sphere_global(t_obj *data, t_vector ray, size_t *i, int shade);
double		plane_intersection(t_obj *data, t_pl *p, t_vector ray, int type);
double		plane_global(t_obj *data, t_vector ray, size_t *i, int shade);
double		cone_top_btm(t_obj *data, t_cn *cone, t_vector direction, int type);
double		dot(t_vector v1, t_vector v2);
t_save		*line_list(int fd);
t_obj		*calculatebtmleft(t_obj *data);
t_obj		*parse(int ac, char **av);
t_obj		*filling_data(char **file_line, t_obj *data);
t_pl		f_p_cy(t_cy *y);
t_pl		*origin_direction_pl(t_pl *y);
t_pl		**filling_pl(char **line, int size, t_obj *data);
t_cy		*origin_direction(t_cy *y);
t_cy		**filling_cy(char **line, int size, t_obj *data);
t_sp		**filling_sp(char **line, int size, t_obj *data);
t_sp		*sphere_tools(t_sp *sphere, char **splite);
t_cn		*filling_cn(char *line);
t_a			*filling_a(char *line);
t_c			*filling_c(char *line);
t_l			**filling_l(char **line, int size, t_obj *data);
size_t		file_size(char **str);
size_t		no_multi_space_size(char *line);
size_t		ft_strlen(char *str);
size_t		lst_size(t_save *list);
char		**remove_line_break(char **file_name);
char		*ft_strtrim(char *s1, char *set);
char		*ft_reading_to_stock(int fd, char *stock);
char		*ft_liner(char *stock);
char		*ft_stockage(char *stock);
char		*get_next_line(int fd);
char		*ft_strcpy(char *dest, char *src);
char		*ft_strdup(char *src);
char		*ft_strjoin(char *s1, char *s2);
char		*new_line(char *line);
char		**finding_multiple_element(int *len, char **file_line, char *twin);
char		**filling_lines(char *file);
char		*searching_for(char **file_line, char *type);
char		**line_maker(t_save *list);
char		**ft_split(char const *s, char c);
void		setup_camera(t_obj *data);
void		exec_part(t_obj *data);
void		ft_strcat(char *str, char *dest, char *src);
void		error_print(int num);
void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
void		clear_list(t_save **list);
void		free_double(char **str);
void		remove_multiple_space(char **file_line);
void		ft_matrix(char *str, double *x, double *y, double *z);
void		my_mlx_pixel_put(t_obj *data, int i, int j, int color);
void		ray_tracer(t_obj *data);
void		drawing_func(t_obj *data);
void		free_struct(t_obj *data);
void		uv_checker(t_sp *data_sp, double *u, double *v, t_vector hitpoint);
int			ambient_lighting(t_obj *data, t_vector ray, t_cyin in, int type);
int			is_equal(t_vector v1, t_vector v2);
int			clamp(int c);
int			check_bumb(char *file);
int			set_color(int R, int G, int B);
int			controling_windows_man(int keycode, t_vars *vars);
int			exit_(t_vars *vars);
int			ft_strchr(char *s, int c);
int			intersection(t_obj *data, t_vector ray, int *color);
int			multi_space(char *line);
int			signe_init(char *str, int *i);
int			matrix_correct(char *str);
int			check_rgb(char *str);
int			ambient_lightning_protection(char *line);
int			check_num(char *str, size_t *i);
int			check_num_beta(char *str, size_t *i);
int			xyz_correct(char *str);
int			check_xyz_axis(char **matrix);
int			xyz_vectors_correct(char *str);
int			fov_range(char *str);
int			camera_protection(char *line);
int			brightness_ratio_range(char *str);
int			light_protection(char *line);
int			sphere_diam_correct(char *str);
int			sphere_protection(char *line);
int			plane_protection(char *line);
int			cn_protection(char *line);
int			cylinder_protection(char *line);
int			protection_tool(char *lines, int *flag_a, int *flag_c, int *flag_l);
int			protection_tool_two(char *lines, int *i);
int			protections(char **lines);
int			splite_size(char **str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			type_check(char *file);
int			find_twins_elements(char **file_line, char *twin);
int			parssing(char *file, t_obj *data);
int			ft_atoi(char *str);
int			check_board(char *file);
int			clamp_(int v, int min, int max);
int			ambient_lighting(t_obj *data, t_vector ray, t_cyin in, int type);
#endif
