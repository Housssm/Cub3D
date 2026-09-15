NAME        = cub3d

CC          = cc
CFLAGS      = -Wall -Wextra -Werror

LIBFT_DIR   = Libft/libft
LIBFT       = $(LIBFT_DIR)/libft.a

GNL_DIR     = Libft/GNL
GNL         = $(GNL_DIR)/get_next_line.a

PRINTF_DIR  = Libft/printf
PRINTF      = $(PRINTF_DIR)/libftprintf.a

MLX_DIR     = minilibx-linux
MLX         = $(MLX_DIR)/libmlx.a
MLX_FLAGS   = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

COMMON_SRCS =   Src/parsing/init.c \
                Src/parsing/check_args.c \
                Src/parsing/parsing_utils.c \
                Src/parsing/check_map.c \
                Src/parsing/map_closed.c \
                Src/parsing/flood_fill.c \
                Src/parsing/check_texture.c \
                Src/parsing/check_color.c \
                Src/parsing/check_color_utils.c \
                Src/parsing/extract_lines.c \
                Src/parsing/build_map.c \
                Src/parsing/parse_config.c \
                Src/parsing/parsing.c \
                Src/raycasting/game_initiation.c \
                Src/raycasting/scene.c \
                Src/raycasting/make_it_clean.c \
                Src/raycasting/keyboard_input.c \
                Src/raycasting/player_mouvement.c \
                Src/raycasting/dda.c \
                Src/raycasting/dda2.c \
                Src/raycasting/dda3.c

MAND_SPEC   =   Src/main.c \
                Src/raycasting/texture_drawing.c

BONUS_SPEC  =   Src/main_bonus.c \
                Src/raycasting/texture_drawing_bonus.c \
                Src/raycasting/minimap.c

COMMON_OBJS = $(COMMON_SRCS:.c=.o)
OBJS_MAND   = $(COMMON_OBJS) $(MAND_SPEC:.c=.o)
OBJS_BONUS  = $(COMMON_OBJS) $(BONUS_SPEC:.c=.o)

INCLUDES    =   -I Includes \
                -I $(LIBFT_DIR) \
                -I $(GNL_DIR) \
                -I $(PRINTF_DIR) \
                -I $(MLX_DIR)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(GNL):
	$(MAKE) -C $(GNL_DIR)

$(PRINTF):
	$(MAKE) -C $(PRINTF_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(LIBFT) $(GNL) $(PRINTF) $(MLX) $(OBJS_MAND)
	rm -f .bonus
	$(CC) $(CFLAGS) $(OBJS_MAND) $(PRINTF) $(GNL) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

bonus: .bonus

.bonus: $(LIBFT) $(GNL) $(PRINTF) $(MLX) $(OBJS_BONUS)
	rm -f $(NAME)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(PRINTF) $(GNL) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	touch .bonus

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS_MAND) $(OBJS_BONUS) .bonus
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(GNL_DIR) clean
	$(MAKE) -C $(PRINTF_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(GNL_DIR) fclean
	$(MAKE) -C $(PRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus