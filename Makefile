NAME            = cube3D

# -------------------- Colors --------------------
GREEN           = \033[0;32m
BLUE            = \033[0;34m
YELLOW          = \033[0;33m
NC              = \033[0m

# -------------------- Compiler --------------------
CC              = cc
CFLAGS          = -Wall -Wextra -Werror -g3
ifdef OPTI
	CFLAGS += -O3
endif
MLX_FLAGS		= -L $(MLX_PATH) -lmlx -lXext -lX11 -O3
RM              = rm -rf

# -------------- Configuration Valgrind -------------
VAL_BIN   = valgrind
VAL_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes #--quiet
MAP = maps/good/subject_map.cub

# -------------------- Directories --------------------
SRC_DIR         = srcs
OBJ_DIR         = obj
INC_DIR         = includes 

#--------------------Subdirectories--------------------
MLX_DIR			= mlx
PARSING_DIR		= parsing
RAYCASTING_DIR	= raycasting
UTILS_DIR		= utils

# -------------------- Libraries --------------------
LIBFT_DIR       = libft
LIBFT           = $(LIBFT_DIR)/libft.a
MLX_PATH		= minilibx-linux
MINILIBX		= $(MLX_PATH)/libmlx_Linux.a
INCLUDES        = -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_PATH)

#---------------------Files-----------------------
MAIN_FILES		= main.c
MLX_FILES		= hooks.c movment.c set_img.c
PARSING_FILES	=	init1.c\
					init2.c\
					map_parse.c\
					parsing.c\
					pre_map.c\
					temp_map_tool.c\
					texture_color.c 
RAYCASTING_FILES = 	raycasting.c\
					raycasting2.c\
					raycasting3.c\
					render.c\
					render2.c
UTILS_FILES		=	debug.c\
					ft_free.c\
					utils.c\
					tools.c

# -------------------- Srcs --------------------
SRC_FILES       =	$(MAIN_FILES)\
					$(addprefix $(MLX_DIR)/,$(MLX_FILES))\
					$(addprefix $(PARSING_DIR)/,$(PARSING_FILES))\
					$(addprefix $(RAYCASTING_DIR)/,$(RAYCASTING_FILES))\
					$(addprefix $(UTILS_DIR)/,$(UTILS_FILES))

SRCS            = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

# -------------------- Objects --------------------
OBJS            = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS            = $(OBJS:.o=.d)

# -------------------- Rules --------------------
all: $(LIBFT) $(MINILIBX) $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MINILIBX)
	@# Ajout de -lm à la fin pour les calculs de raycasting
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MINILIBX) $(MLX_FLAGS) -lm -o $(NAME) -g
	@echo "✨$(GREEN) $(NAME) is ready to run !$(NC)✨"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

$(MINILIBX):
	@$(MAKE) -C $(MLX_PATH) --no-print-directory

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@
	@echo "$(YELLOW)Compiling: $< $(NC)"

val: all
	@echo "Running Cub3D with Valgrind...$(RESET)"
	$(VAL_BIN) $(VAL_FLAGS) ./$(NAME) $(MAP)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@$(MAKE) -C $(MLX_PATH) clean --no-print-directory
	@$(RM) $(OBJ_DIR)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@$(RM) $(NAME)
	@echo "🧼$(BLUE) All clean !$(NC)🧼"

re: fclean all

phrase:
	@echo "$(BLUE)Ah s***, here we go again ...$(NC)"

bonus: all

-include $(DEPS)

.PHONY: all clean fclean re bonus phrase
