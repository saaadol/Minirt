
NAME = MiniRT
SRC =	cone.c Main.c	vector.c Parssing.c	get_next_line.c	get_next_line_utils.c	utils.c execution.c drawing.c  cy_routine.c sp_routine.c pl_routine.c diffuse.c textures.c
SRC_BONUS = 
MLXFRAME = -lmlx -framework OpenGL -framework AppKit
CFLAGS =-Wall -Wextra -Werror -g #-fsanitize=thread
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