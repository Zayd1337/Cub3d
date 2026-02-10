NAME            = minishell

# -------------------- Colors --------------------
GREEN           = \033[0;32m
BLUE            = \033[0;34m
YELLOW          = \033[0;33m
NC              = \033[0m

# -------------------- Compiler --------------------
CC              = cc
CFLAGS          = -Wall -Wextra -Werror -g
MLX_FLAGS		= -L $(MLX_PATH) -lmlx -lXext -lX11
RM              = rm -rf

# -------------------- Directories --------------------
SRC_DIR         = srcs
OBJ_DIR         = obj
INC_DIR         = includes 

# -------------------- Libraries --------------------
LIBFT_DIR       = libft
LIBFT           = $(LIBFT_DIR)/libft.a
MLX_PATH		= minilibx-linux
MINILIBX		= $(MLX_PATH)/libmlx_Linux.a
INCLUDES        = -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_PATH)

# -------------------- Srcs --------------------
# On ajoute le dossier srcs/ devant chaque fichier pour que la substitution fonctionne
SRC_FILES       = main.c parsing.c raycasting.c
SRCS            = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

# -------------------- Objects --------------------
# On transforme srcs/file.c en obj/file.o
OBJS            = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS            = $(OBJS:.o=.d)

# -------------------- Rules --------------------
all: $(LIBFT) $(MINILIBX) $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MINILIBX)
	@# Ajout de -lm à la fin pour les calculs de raycasting
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MINILIBX) $(MLX_FLAGS) -lm -o $(NAME)
	@echo "✨$(GREEN) $(NAME) is ready to run !$(NC)✨"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

$(MINILIBX):
	@$(MAKE) -C $(MLX_PATH) --no-print-directory

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@
	@echo "$(YELLOW)Compiling: $< $(NC)"

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@$(MAKE) -C $(MLX_PATH) clean --no-print-directory
	@$(RM) $(OBJ_DIR)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@$(RM) $(NAME)
	@echo "🧼$(BLUE) All clean !$(NC)🧼"

re: fclean phrase all

phrase:
	@echo "$(BLUE)Ah s***, here we go again ...$(NC)"

bonus: all

-include $(DEPS)

.PHONY: all clean fclean re bonus phrase