NAME = RT_SCENE

FLAGS = -Wall -Wextra -Werror -lmlx -framework OpenGL -framework AppKit -lpthread

HEAD =  -L ../minilibx_macos/ -I include/rt.h ../libft/libft.h

SRC_RT_PARSER = resources/parser/

FILE_NAME_PARSER = parser.c parse_object1.c parser_block.c parse_light_cam.c string_parse_func.c parser_texture_shadows.c parse_param.c parse_disk.c parse_cone_triangle.c parse_obj_plane_tube.c  additional.c 

SRC_RT_INTRSECT = resources/intersection/

FILENAME_INTRSECT = find_standart_obj_normals.c find_new_shapes_normals.c intersect_standart_obj.c intersect_new_shapes.c intersect_cylinder.c intersect_lim_cylinder.c intersect_tube.c

SRC_RT_TRACER = resources/tracer/

FILE_NAME_TRACER = main.c antialiasing.c ray_tracer.c rotation.c reflection_refrection.c filters.c make_color_shadows.c highlight_bases.c

SRC_RT_TEXTURE = resources/texture/

FILE_NAME_TEXTURE = texture_map.c

SRC_RT = $(addprefix $(SRC_RT_PARSER), $(FILE_NAME_PARSER)) $(addprefix $(SRC_RT_INTRSECT), $(FILENAME_INTRSECT)) $(addprefix $(SRC_RT_TRACER), $(FILE_NAME_TRACER)) $(addprefix $(SRC_RT_TEXTURE), $(FILE_NAME_TEXTURE))

SRCO_RT = $(SRC_RT:%.c=%.o)

RED = \033[0;31m

GREEN = \033[0;32m

NC = \033[0m

all: $(NAME)

$(NAME): $(SRCO_RT)
	@ gcc -o $(NAME) $(FLAGS) $(SRCO_RT)  -L ../minilibx_macos/ ../libft/libft.a 

%.o: %.c $(HEAD)
	@ gcc -c $(FLAGS) -o $@ $<
	
clean:
	@ rm -f $(SRCO_RT)

fclean: clean
	@ rm -rf $(NAME)

re: fclean all
