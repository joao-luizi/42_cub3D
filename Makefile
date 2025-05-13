CC				=	cc
CFLAGS 			= 	-Wall -Wextra -Werror -g -I$(MLX_PATH)
RM				=	rm -rf

SRC_DIR			= ./src
SRC_DIR_BO		= ./src_bonus
OBJ_DIR 		= ./obj
INC_DIR			= ./inc
BIN_DIR			= ./bin
LIB_DIR			= ./lib
NAME			=	${BIN_DIR}/cub3D
NAME_BONUS		=	${BIN_DIR}/cub3D_bonus

LIBFT_PATH		=	$(addprefix $(LIB_DIR)/, libft/)
LIBFT_FILE		=	$(LIBFT_PATH)lib/libft.a

MLX_PATH		=	$(addprefix $(LIB_DIR)/, minilibx-linux/)
MLX_FILE		=	$(MLX_PATH)libmlx.a

LINKS 			= -lmlx -lXext -lX11 -L$(MLX_PATH) -lmlx -L$(LIBFT_PATH)lib -lft -lm

SRC				=	$(SRC_DIR)/render/render_utils.c $(SRC_DIR)/render/main_scene.c $(SRC_DIR)/render/render_perf.c  \
					$(SRC_DIR)/game/init.c $(SRC_DIR)/game/hooks.c $(SRC_DIR)/game/game.c $(SRC_DIR)/setup/setup.c \
					$(SRC_DIR)/common/aux.c $(SRC_DIR)/common/init.c $(SRC_DIR)/common/cleanup.c\
					$(SRC_DIR)/setup/aux.c $(SRC_DIR)/setup/setup_fields.c $(SRC_DIR)/setup/setup_map.c\
					$(SRC_DIR)/main.c 

SRC_BONUS		=	$(SRC_DIR_BO)/setup/setup.c $(SRC_DIR_BO)/setup/init.c $(SRC_DIR_BO)/setup/cleanup.c\
					$(SRC_DIR_BO)/setup/aux.c $(SRC_DIR_BO)/setup/setup_fields.c $(SRC_DIR_BO)/setup/setup_map.c\
					$(SRC_DIR_BO)/main.c $(SRC_DIR_BO)/aux.c

OBJS 			= 	${patsubst ${SRC_DIR}/%.c, ${OBJ_DIR}/%.o, ${SRC}}

OBJS_BONUS		= 	${patsubst ${SRC_DIR}/%.c, ${OBJ_DIR}/%.o, ${SRC_BONUS}}

all:	$(NAME)

$(OBJ_DIR):
	@if [ ! -d $(OBJ_DIR) ]; then mkdir -p $(OBJ_DIR); fi

$(BIN_DIR):
	@if [ ! -d $(BIN_DIR) ]; then mkdir -p $(BIN_DIR); fi

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_FILE):
	@echo "Building libft..."
	make -C $(LIBFT_PATH)

$(MLX_FILE):
	@echo "Building MiniLibX..."
	make -C $(MLX_PATH)

$(NAME):	$(OBJS) $(LIBFT_FILE) $(MLX_FILE) $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LINKS)

bonus:	$(NAME_BONUS)

$(NAME_BONUS):	$(OBJS_BONUS) $(LIBFT_FILE) $(MLX_FILE) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJS_BONUS) -o $@ $(LINKS)

clean:
	@if [ -d $(OBJ_DIR) ]; then $(RM) $(OBJ_DIR); fi
	@if [ -f $(NAME) ]; then $(RM) $(NAME); fi
	@if [ -f $(NAME_BONUS) ]; then $(RM) $(NAME_BONUS); fi

fclean:		clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT_PATH)
	make clean -C $(MLX_PATH)

re:	fclean all

.PHONY: all clean fclean re