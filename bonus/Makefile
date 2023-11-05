NAME = MiniRT
SRC = loading_texture.c free_bonus.c cone.c ft_strtrim.c camera.c color.c cy_routine.c cylinder.c diffuse.c execution.c get_next_line.c get_next_line_utils.c intersection.c light_utils.c light.c Main.c memset_calloc.c Parssing.c parssing_utils.c parssing_utils_1.c parssing_utils_2.c parssing_utils_3.c parssing_utils_4.c parssing_utils_5.c parssing_utils_6.c parssing_utils_7.c parssing_utils_8.c parssing_utils_9.c parssing_utils_10.c pl_routine.c plane.c raytracing.c shade.c sphere.c split.c utils.c vecrot_utils.c vector.c diffuse_extra.c diffuse_extra2.c ambient_light.c
SRC_BONUS = 
MLXFRAME = -lmlx -framework OpenGL -framework AppKit
CFLAGS = -Wall -Wextra -Werror -g
OBJS = $(SRC:.c=.o)
OBJS_BONUS = $(SRC_BONUS:.c=.o)
R        := $(shell tput -Txterm setaf 1)
G        := $(shell tput -Txterm setaf 2)
Y       := $(shell tput -Txterm setaf 3)

all: $(NAME)
	@echo $(G) "ALL functions are done!"

$(NAME): $(OBJS)
	@echo $(Y) Compiling: $< ... Done!
	@cc $(CFLAGS) $(MLXFRAME) $(OBJS) -o $@

%.o: %.c Minirt.h
	@echo $(Y) Compiling: $< ... Done!
	@cc $(CFLAGS) -c $<

bonus: ${OBJS_BONUS}
	@echo $(Y) Compiling: $< ... Done!
	@cc $(CFLAGS) $(MLXFRAME) $(OBJS_BONUS) -o $(NAME)

clean:
	@echo $(R) Cleaned
	@rm -f $(OBJS)

fclean: clean
	@echo $(R) Fully cleaned
	@rm -f $(NAME) $(OBJS_BONUS)

re: fclean all

.PHONY: clean fclean re bonus all