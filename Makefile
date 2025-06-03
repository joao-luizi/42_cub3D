CC				=	cc
CFLAGS 			= 	-Wall -Wextra -Werror -MMD -g -I$(MLX_PATH)
RM				=	rm -rf

SRC_DIR			= ./src
SRC_DIR_BO		= ./src_bonus
OBJ_DIR 		= ./obj
OBJ_DIR_BO		= ./obj_bonus
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

SRC				=	$(SRC_DIR)/render/render_utils.c $(SRC_DIR)/render/main_scene.c $(SRC_DIR)/render/render_perf.c  			\
					$(SRC_DIR)/game/init.c $(SRC_DIR)/game/hooks.c $(SRC_DIR)/game/game.c $(SRC_DIR)/game/aux.c \
					$(SRC_DIR)/common/aux.c $(SRC_DIR)/common/init.c $(SRC_DIR)/common/cleanup.c								\
					$(SRC_DIR)/setup/aux.c $(SRC_DIR)/setup/setup_fields.c $(SRC_DIR)/setup/setup_map.c $(SRC_DIR)/setup/setup.c\
					$(SRC_DIR)/main.c 

SRC_BONUS		=	$(SRC_DIR_BO)/render/render_utils.c $(SRC_DIR_BO)/render/main_scene.c $(SRC_DIR_BO)/render/raycast.c \
					$(SRC_DIR_BO)/render/render_perf.c $(SRC_DIR_BO)/render/render_horizontal.c $(SRC_DIR_BO)/render/dda.c\
					$(SRC_DIR_BO)/asc_strings/digits_0_4.c $(SRC_DIR_BO)/asc_strings/digits_5_9.c $(SRC_DIR_BO)/asc_strings/letters_a_e.c $(SRC_DIR_BO)/asc_strings/letters_f_j.c \
					$(SRC_DIR_BO)/asc_strings/letters_k_o.c $(SRC_DIR_BO)/asc_strings/letters_p_t.c $(SRC_DIR_BO)/asc_strings/letters_u_x.c $(SRC_DIR_BO)/asc_strings/letters_y_z.c \
					$(SRC_DIR_BO)/asc_strings/patterns.c $(SRC_DIR_BO)/asc_strings/symbols.c $(SRC_DIR_BO)/asc_strings/write_string.c \
					$(SRC_DIR_BO)/render/minimap.c $(SRC_DIR_BO)/render/minimap_color.c $(SRC_DIR_BO)/render/minimap_wall.c \
					$(SRC_DIR_BO)/render/post_process.c $(SRC_DIR_BO)/render/render_vertical.c $(SRC_DIR_BO)/render/tex_utils.c 		\
					$(SRC_DIR_BO)/game/minimap.c $(SRC_DIR_BO)/game/init.c $(SRC_DIR_BO)/game/hooks.c $(SRC_DIR_BO)/game/hooks_b.c \
					$(SRC_DIR_BO)/game/game.c $(SRC_DIR_BO)/game/aux.c $(SRC_DIR_BO)/game/aux_b.c $(SRC_DIR_BO)/game/game_loop.c	\
					$(SRC_DIR_BO)/common/aux.c $(SRC_DIR_BO)/common/init.c $(SRC_DIR_BO)/common/cleanup.c $(SRC_DIR_BO)/common/cleanup_b.c $(SRC_DIR_BO)/common/cleanup_g.c		\
					$(SRC_DIR_BO)/setup/aux.c $(SRC_DIR_BO)/setup/setup_animation.c $(SRC_DIR_BO)/setup/setup_fields.c \
					$(SRC_DIR_BO)/setup/setup_map.c $(SRC_DIR_BO)/setup/setup_map_utils.c $(SRC_DIR_BO)/setup/setup.c \
					$(SRC_DIR_BO)/main.c 

OBJS 			= 	${patsubst ${SRC_DIR}/%.c, ${OBJ_DIR}/%.o, ${SRC}}

OBJS_BONUS		= 	${patsubst ${SRC_DIR_BO}/%.c, ${OBJ_DIR_BO}/%.o, ${SRC_BONUS}}

DEPS 			=	$(OBJS:.o=.d)

DEPS_BONUS 		=	$(OBJS_BONUS:.o=.d)

all:	$(NAME)

$(OBJ_DIR_BO):
	@if [ ! -d $(OBJ_DIR_BO) ]; then mkdir -p $(OBJ_DIR_BO); fi

$(OBJ_DIR):
	@if [ ! -d $(OBJ_DIR) ]; then mkdir -p $(OBJ_DIR); fi

$(BIN_DIR):
	@if [ ! -d $(BIN_DIR) ]; then mkdir -p $(BIN_DIR); fi

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR_BO)/%.o:	$(SRC_DIR_BO)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPS)
-include $(DEPS_BONUS)

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
	@if [ -d $(OBJ_DIR_BO) ]; then $(RM) $(OBJ_DIR_BO); fi
	@if [ -f $(NAME) ]; then $(RM) $(NAME); fi
	@if [ -f $(NAME_BONUS) ]; then $(RM) $(NAME_BONUS); fi

fclean:		clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT_PATH)
	make clean -C $(MLX_PATH)

re:	fclean all

.PHONY: all clean fclean re