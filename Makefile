# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/22 23:12:10 by pbondoer          #+#    #+#              #
#    Updated: 2024/09/19 00:19:46 by myokono          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        =   fdf
BONUS_NAME  =   fdf_bonus

SRC         =   src/fdf.c src/draw.c src/hook.c src/lineclip.c src/free.c src/map.c \
				src/reader.c src/image.c src/init.c src/utils.c src/color.c \
				src/list.c src/cal.c src/line.c

BONUS_SRC   =   src_bonus/fdf.c src_bonus/draw.c src_bonus/hook.c src_bonus/lineclip.c \
				src_bonus/free.c src_bonus/map.c src_bonus/reader.c src_bonus/image.c \
				src_bonus/init.c src_bonus/utils.c src_bonus/color.c src_bonus/mouse.c

OBJS        =   $(SRC:.c=.o)
BONUS_OBJS  =   $(BONUS_SRC:.c=.o)

CC          =   gcc

CFLAGS      =   -Wall -Wextra -Werror -Iincludes -Ilibft -g

CFLAGS		+= -g -fsanitize=address


MLX_FLAGS   =   -Lminilibx -lmlx -framework OpenGL -framework AppKit

LIBFT       =   libft/libft.a
LIBFT_FLAGS =   -Llibft -lft

RM          =   rm -f

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS) $(LIBFT_FLAGS)

$(LIBFT):
			make -C libft

bonus: $(LIBFT) $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJS)
			$(CC) $(CFLAGS) -o $(BONUS_NAME) $(BONUS_OBJS) $(MLX_FLAGS) $(LIBFT_FLAGS)

clean:
			$(RM) $(OBJS) $(BONUS_OBJS)
			make clean -C libft

fclean: clean
			$(RM) $(NAME) $(BONUS_NAME)
			make fclean -C libft

re: fclean all

.PHONY: all clean fclean re bonus
