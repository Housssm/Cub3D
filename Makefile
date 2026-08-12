# **************************************************************************** #
#                                   cub3D                                      #
# **************************************************************************** #

NAME		= cub3d

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

# ----------------------------- Libraries ----------------------------------- #

LIBFT_DIR	= Libft/libft
LIBFT		= $(LIBFT_DIR)/libft.a

GNL_DIR		= Libft/GNL
GNL			= $(GNL_DIR)/get_next_line.a

PRINTF_DIR	= Libft/printf
PRINTF		= $(PRINTF_DIR)/libftprintf.a

MLX_DIR		= minilibx-linux
MLX			= $(MLX_DIR)/libmlx.a
MLX_FLAGS	= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# ----------------------------- Sources ------------------------------------- #

SRCS		=	Src/main.c \
				Src/parsing/init.c \
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
				Src/game_initiation.c\
				Src/make_it_clean.c\
				Src/keyboard_input.c\
				Src/player_mouvement.c\
				Src/dda.c\
				Src/dda2.c\
				Src/dda3.c\
				Src/texture_drawing.c\
				Src/minimap.c

OBJS		= $(SRCS:.c=.o)

INCLUDES	=	-I Includes \
				-I $(LIBFT_DIR) \
				-I $(GNL_DIR) \
				-I $(PRINTF_DIR) \
				-I $(MLX_DIR)

# ----------------------------- Rules --------------------------------------- #

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(GNL):
	$(MAKE) -C $(GNL_DIR)

$(PRINTF):
	$(MAKE) -C $(PRINTF_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(LIBFT) $(GNL) $(PRINTF) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(PRINTF) $(GNL) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
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

.PHONY: all clean fclean re