NAME = Fdf

LIBFT = Libft/libft.a
FT_PRINTF = ft_printf/libftprintf.a
SRC_DIR = src/

CC = gcc
CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -framework OpenGL -framework AppKit
RM = rm -f


SRCS = 		$(SRC_DIR)fdf.c \
			$(SRC_DIR)errors.c \


OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(MLX_FLAGS) $(OBJS) libmlx.a $(LIBFT) $(FT_PRINTF) -o $(NAME)

all: $(NAME)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re: fclean all

.PHONY:	all clean fclean re
