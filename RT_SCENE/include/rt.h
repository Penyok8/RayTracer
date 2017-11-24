/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <ozhovnuv@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 16:58:00 by ozhovnuv          #+#    #+#             */
/*   Updated: 2017/07/10 19:45:43 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H
# include "../../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include "../../minilibx_macos/mlx.h"
# include <stdlib.h>
# include <pthread.h>
# include <sys/types.h>

# define HEIGHT 1200
# define WIDTH 1800
# define FOV 60
# define INV_HEIGHT (1 / (double)HEIGHT)
# define INV_WIDTH (1 / (double)WIDTH)
# define ASP_RATIO (WIDTH / (double)HEIGHT)
# define ANGLE (tan(FOV / 2 * M_PI / 180.0))
# define DEGREE(x) ((double)x * M_PI / 180.0)
# define SIN(x) sin(x * M_PI / 180.0)
# define COS(x) cos(x * M_PI / 180.0)
# define SPHERE 0
# define CYLINDER 1
# define PLANE 2
# define CONE 3
# define TORUS 4
# define BOX 5
# define DISK 6
# define TRIANGLE 7
# define LIMITED_CYLINDER 8
# define LIMITED_CONE 9
# define ELLIPSE 10
# define TUBE 11
# define DARK_C 220
# define MAX_DEPTH 10

# define RED (t_color){0, 0, 255, 0}
# define GREEN (t_color){0, 255, 0, 0}
# define BLUE (t_color){255, 0, 0, 0}
# define CYAN (t_color){255, 255, 0, 0}
# define YELLOW (t_color){0, 255, 255, 0}
# define MAGENTA (t_color){255, 0, 255, 0}
# define WHITE (t_color){255, 255, 255, 0}
# define BLACK (t_color){0, 0, 0, 0}
# define VINOUS (t_color){20, 0, 20, 0}

# define FIL_NEG 1
# define FIL_B_W 2

# define POINT_LIGHT 201
# define DIRECTIONAL_LIGHT 202
# define PARALLEL_LIGHT 203

# define ERROR_NUM_NOT_CORRECT 111
# define ERROR_PARSE_BLOCK 112
# define ERROR_NOT_VALID_COLOR 113
# define ERROR_NOT_VALID_VECTOR 114
# define ERROR_NUMBER_NOT_EXIST 115
# define ERROR_NOT_VALID_PARAM 116
# define ERROR_BLOCK_NOT_EXIST 117
# define ERROR_NOT_VALID_CAM 118
# define ERROR_NOT_CORRECT_FILE 119
# define ERROR_NOT_VALID_PLANE 120
# define ERROR_TEXTURE_FILE 121
# define ERROR_LIGHT_TYPE 122
# define ERROR_EMPTY_LINE 123
# define ERROR_GLOSY 124
# define ERROR_FILTER_NOT_EXIST 125

# define D_V0 (t_vector){0, 0, 0}
# define D_DIR (t_vector){0, 1, 0}
# define DEF_SPHERE (t_sphere){D_V0, 200}
# define DEF_CYL (t_cylinder){D_V0, D_DIR, 200}
# define DEF_PL (t_plane){(t_vector){0, -500, 0}, D_DIR, 0}
# define DEF_CONE (t_cone){D_V0, D_DIR, 10}
# define DEF_DISK (t_disk){D_V0, D_DIR, 100, 0}
# define DEF_ELL (t_ellips){D_V0, (t_vector){100, 50, 100}}
# define DEF_TUBE (t_tube){D_V0, D_DIR, 10, 10}
# define DEF_LCYL (t_lcylinder){}
# define DEF_TR (t_triangle){D_V0, D_V0, D_V0}

typedef	struct		s_block
{
	char			*line;
	struct s_block	*next;
}					t_block;

typedef struct		s_color
{
	double			r;
	double			g;
	double			b;
	double			a;
}					t_color;

typedef struct		s_texture
{
	t_color			**rgb;
	t_vector		v_y;
	t_vector		v_x;
	t_vector		v_p;
	t_vector		tmp;
	void			*xpm;
	char			*data;
	int				sizeline;
	int				w;
	int				h;
	double			phi;
	double			theta;
	double			u;
	double			v;
}					t_texture;

typedef struct		s_obj
{
	void			*obj;
	int				(*intersection)();
	t_vector		(*find_normal)();
	void			(*texture_obj)();
	double			reflection;
	double			refrection;
	double			transparency;
	int				glosy;
	t_color			color;
	t_texture		*texture;
	struct s_obj	*next;
}					t_obj;

typedef struct		s_session
{
	void			*ini;
	char			*data;
	void			*mlx;
	void			*win;
	int				bpp;
	int				sizeline;
	int				endian;
}					t_session;

typedef struct		s_light
{
	t_vector		pos;
	t_vector		dir;
	int				type;
	double			angle;
	double			intensity;
	struct s_light	*next;
}					t_light;

typedef struct		s_sphere
{
	t_vector		centre;
	double			radius;
}					t_sphere;

typedef struct		s_cylinder
{
	t_vector		pos;
	t_vector		rot;
	double			radius;
}					t_cylinder;

typedef struct		s_lcylinder
{
	t_vector		bottom;
	t_vector		top;
	t_vector		centre;
	double			radius;
	t_vector		rot;
	double			length;
}					t_lcylinder;

typedef struct		s_cone
{
	t_vector		pos;
	t_vector		rot;
	double			angle;
}					t_cone;

typedef struct		s_lcone
{
	t_vector		bottom;
	t_vector		top;
	double			bradius;
	double			tradius;
	double			angle;
	t_vector		centre;
	t_vector		rot;
}					t_lcone;

typedef struct		s_plane
{
	t_vector		pos;
	t_vector		normal;
	double			sphere_radius;
}					t_plane;

typedef struct		s_disk
{
	t_vector		pos;
	t_vector		normal;
	double			radius;
	double			in_radius;
}					t_disk;

typedef	struct		s_ellipse
{
	t_vector		position;
	t_vector		size;
}					t_ellipse;

typedef struct		s_triangle
{
	t_vector		v0;
	t_vector		v1;
	t_vector		v2;
	t_vector		e1;
	t_vector		e2;
	t_vector		normal;
}					t_triangle;

typedef	struct		s_ray
{
	t_vector		start;
	t_vector		dir;
}					t_ray;

typedef struct		s_tube
{
	t_vector		pos;
	t_vector		rot;
	double			radius;
	double			len;
	t_vector		top;
	t_vector		bottom;
}					t_tube;

typedef struct		s_main
{
	t_obj			*obj;
	t_light			*light;
	t_ray			cam;
	t_vector		cam_rotation;
	int				ss_rays;
	int				ss_radius;
	int				ss_ray_iter;
	int				filter;
	t_obj			*color_obj;
	double			t;
	double			temp_t;
	t_vector		dist_to_light;
	int				threads_num;
}					t_main;

typedef struct		s_thread
{
	int				thread_num;
	t_main			main;
	t_session		*session;
}					t_thread;

void				parser(int fd, t_main *main, t_session *session);
void				parse_error(int error);
int					parse_error_plus(int error);
void				parse_param(char *param, char *str, t_obj **obj,
									t_session *session);
double				parse_number(char *str);
t_vector			parse_vector(char *str);
t_color				parse_color(char *str);
void				parse_cam(t_block *head, t_main *main);
void				parse_light(t_block *head, t_light **obj, char *type);
int					parser_obj_equation(char *str, int fd, t_session *session,
											t_obj **obj);
void				parse_soft_shadows(t_block *head, t_main *main);
int					parse_glosy(char *str);
t_block				*get_block(int fd);
void				push_block(t_block *head, char *line);
void				free_block(t_block *head);

void				obj_create(t_obj **head);
void				obj_add(t_obj *head, void *obj, int type);
void				obj_param_add(t_obj *head, double param, int param_type);
void				obj_color_add(t_obj *head, t_color color);
void				obj_texture_add(char *str, t_obj *obj, t_session *session);

int					light_type(char *type);
void				light_create(t_light **light, int type);
void				light_equalize(t_light *head);

void				parse_filter(t_block *head, t_main *main);
void				add_filter(t_main *main, t_session *ses);

void				parse_sphere(t_block *head, t_obj **obj,
									t_session *session);
void				parse_cylinder(t_block *head, t_obj **obj,
									t_session *session);
void				parse_lcylinder(t_block *head, t_obj **obj,
									t_session *session);
void				parse_plane(t_block *head, t_obj **obj,
									t_session *session);
void				parse_disk(t_block *head, t_obj **obj,
									t_session *session);
void				parse_cone(t_block *head, t_obj **obj,
									t_session *session);
void				parse_lcone(t_block *head, t_obj **obj,
									t_session *session);
void				parse_tube(t_block *head, t_obj **obj,
									t_session *session);
void				parse_triangle(t_block *head, t_obj **obj,
									t_session *session);
void				parse_ellipse(t_block *head, t_obj **obj,
									t_session *session);
void				parse_capsule(t_block *head, t_obj **obj,
									t_session *session);
void				parse_lcyl(t_lcylinder *c, char *line, t_obj **obj,
									t_session *ses);

void				free_block(t_block *head);
void				free2(char *str, char *str2);
void				free_str_array(char **str, int len);
char				*first_word(char *str);
int					arraylen(char **array);
int					strint(char *str);
int					strdouble(char *str);
double				atod(char *str);

void				*trace(void *thread_elem);
t_obj				*find_intersection(t_ray ray, t_main *main,
										double light_distance);

t_vector			ray_dir_init(t_main *main, double x, double y);
t_vector			rot_x(t_vector dir, double angle);
t_vector			rot_y(t_vector dir, double angle);
t_vector			rot_z(t_vector dir, double angle);

int					intersect_sphere(t_ray *ray, void *obj, t_main *main,
										double d);
int					intersect_cone(t_ray *ray, void *obj, t_main *main,
										double d);
int					intersect_cylinder(t_ray *ray, void *obj, t_main *main,
										double d);
int					intersect_plane(t_ray *ray, void *obj, t_main *main,
										double d);
int					intersect_disk(t_ray *ray, void *obj, t_main *main,
										double d);
int					intersect_lcylinder(t_ray *ray, void *obj, t_main *main,
										double d);
int					intersect_ellipse(t_ray *ray, void *obj, t_main *main,
										double d);
int					intersect_triangle(t_ray *ray, void *obj, t_main *main,
										double d);
int					intersect_tube(t_ray *ray, void *obj, t_main *main,
										double d);
double				min_lc(double t1, double t2, t_main *main);
double				min_p(double t1, double t2, t_main *main);
double				intr_cap(t_vector pos, t_vector normal, double radius,
										t_ray *ray);

t_vector			cyl_abc(t_ray *ray, t_cylinder *cyl, t_vector *dist);
t_vector			cone_abc(t_ray *ray, t_cone *cone, t_vector *dist);
t_color				cast_ray(t_ray ray, int depth, t_main *main);
t_color				reflection_make(t_ray *ray, t_main *main, int depth,
									t_obj *obj);
t_color				refraction_make(t_ray *ray, t_main *main, int depth,
									t_obj *obj);
void				light_dir_ray(t_light *cur, t_ray *sh_ray);

t_color				make_color(t_obj *obj, t_main *main, t_ray *ray);
void				make_color_shadows(t_ray ray, t_color *f_c, t_light *cur,
					t_main *main);
t_vector			define_bases(t_vector *dir);
void				randomize_ray(t_vector *uu, t_vector *vv, t_ray *sh_ray,
					t_light *cur);
void				set_random_dir(t_vector *uuu, t_vector *vvv, t_ray *sh_ray,
					t_light *current);
void				color_inter_obj(t_light *cur, t_ray ray, t_color *f_c,
					t_main *main);
t_ray				find_shadow_ray(t_ray *ray, t_main *main);
t_color				highlight_obj(t_obj *obj, t_ray *ray, t_color color,
					t_light *light);

t_color				color_scale(t_color color, double factor);
t_color				color_add(t_color c1, t_color c2);
t_vector			reflected_ray(t_vector *dir, t_vector *norm);
t_vector			refrected_ray(t_vector *dir, t_vector *norm, double ior);
t_vector			refr_addit(t_vector *et, double cos_i, t_vector *dir,
								t_vector *n);
void				fresnel(t_vector *dir, t_vector *norm, double ior,
								double *kr);
void				fresnel_refl(double cos_i, t_vector eta, double sin_tt,
								double *kr);

void				normal_type(t_obj *obj, int type);
t_vector			normal_sphere(t_ray *ray, void *obj);
t_vector			normal_cylinder(t_ray *ray, void *obj);
t_vector			normal_plane(t_ray *ray, void *obj);
t_vector			normal_cone(t_ray *ray, void *obj);
t_vector			normal_disk(t_ray *ray, void *obj);
t_vector			normal_lcylinder(t_ray *ray, void *obj);
t_vector			normal_ellipse(t_ray *ray, void *obj);
t_vector			normal_triangle(t_ray *ray, void *obj);
t_vector			normal_tube(t_ray *ray, void *obj);

t_texture			*take_xpm(t_session *session, char *file);
void				texture_sphere(void *id, t_obj *obj, t_vector hit_point);
void				texture_plane(void *id, t_obj *obj, t_vector hit_point);
void				texture_cylinder(void *id, t_obj *obj, t_vector hit_point);

t_color				rgba(int r, int g, int b, int alpha);

#endif
