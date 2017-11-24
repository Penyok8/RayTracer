NAME = RT

FLAGS = -Wall -Wextra -Werror -lmlx -framework OpenGL -framework AppKit

HEAD =  -L minilibx_macos/ -I GUI/resources/gui_rt.h libft/libft.h

SRC_RT_PATH = GUI/resources/

SRC_NAME_RT = main.c texture_close.c mouse_action.c

SRC_RT = $(addprefix $(SRC_RT_PATH), $(SRC_NAME_RT))

SRCO_RT = $(SRC_RT:%.c=%.o)

RED = \033[0;31m

GREEN = \033[0;32m

NC = \033[0m

all: $(NAME)
	@echo "${GREEN}-->Project compile<--${NC}"

$(NAME): $(SRCO_RT)
	@ make -C ./libft/
	@ echo "${GREEN}^^Libft compile^^${NC}"
	@ make -C RT_SCENE/
	@ gcc -o $(NAME) $(FLAGS) $(SRCO_RT) libft/libft.a -L minilibx_macos/

%.o: %.c $(HEAD)
	@ gcc -c $(FLAGS) -o $@ $<

clean:
	@ make clean -C ./libft/
	@ make clean -C RT_SCENE/
	@ rm -f $(SRCO_RT)
	@ echo "${RED}Object files are delete${NC}"

fclean: clean
	@ make fclean -C ./libft/
	@ make fclean -C RT_SCENE/
	@ rm -rf $(NAME)
	@ echo "${RED}Binari file delete${NC}"

re: fclean all