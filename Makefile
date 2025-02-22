NAME = Fdf

LIBFT = Libft/libft.a
FT_PRINTF = ft_printf/libftprintf.a
GETNEXTLINE = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
SRC_DIR = src/

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
MLX_FLAGS = -framework OpenGL -framework AppKit
RM = rm -f


SRCS = 		$(SRC_DIR)fdf.c \
			$(SRC_DIR)errors.c \
			$(SRC_DIR)read_file.c \
			$(SRC_DIR)draw.c \
			$(SRC_DIR)init.c \
			$(SRC_DIR)keystrokes.c \
			$(SRC_DIR)hooks.c \
			$(SRC_DIR)draw_utils.c \
			$(SRC_DIR)read_utils.c \
			$(SRC_DIR)utils.c \


OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(MLX_FLAGS) $(OBJS) libmlx.a $(LIBFT) $(FT_PRINTF) $(GETNEXTLINE) -o $(NAME)

all: $(NAME)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re: fclean all

.PHONY:	all clean fclean re
