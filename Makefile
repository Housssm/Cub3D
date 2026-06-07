SRCS = \
		main.c\
		
OBJS = ${SRCS:.c=.o}

NAME = cub3D

HEADER = cub3d.h

LIBFT_DIR = ./Libft/libft
LIBFT = ${LIBFT_DIR}/libft.a

MLX_DIR = ./minilibx-linux
MLX = ${MLX_DIR}/libmlx.a

CC = cc
CFLAGS = -Wall -Werror -Wextra -g3
MLX_FLAGS = -L${MLX_DIR} -lmlx -lXext -lX11 -lm

all: ${NAME}

${NAME}: ${OBJS} ${LIBFT} ${MLX} 
	@${CC} ${CFLAGS} ${OBJS} ${LIBFT} ${MLX_FLAGS} -o ${NAME}

${LIBFT}:
	@make -sC ${LIBFT_DIR}

${MLX}:
	@make -sC ${MLX_DIR}

%.o: %.c ${HEADER}
	@${CC} ${CFLAGS} -I${LIBFT_DIR} -I${MLX_DIR} -c $< -o $@

clean:
	rm -f ${OBJS}
	@make -sC ${LIBFT_DIR} clean
	@make -sC ${MLX_DIR} clean

fclean: clean
	rm -f ${NAME}
	rm -f a.out
	@make -sC ${LIBFT_DIR} fclean
	@make -sC ${MLX_DIR} clean

re: fclean all

.PHONY: all clean fclean re