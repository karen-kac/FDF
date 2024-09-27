# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: myokono <myokono@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/22 23:12:10 by pbondoer          #+#    #+#              #
#    Updated: 2024/09/27 19:02:43 by myokono          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        =   fdf
BONUS_NAME  =   fdf_bonus

SRC         =   src/fdf.c src/draw.c src/hook.c src/line2.c src/free.c src/map.c \
				src/reader.c src/image.c src/init.c src/utils.c src/color.c \
				src/list.c src/cal.c src/line.c

BONUS_SRC   =   src_bonus/fdf_bonus.c src_bonus/draw_bonus.c src_bonus/hook_bonus.c src_bonus/line2_bonus.c \
				src_bonus/free_bonus.c src_bonus/map_bonus.c src_bonus/reader_bonus.c src_bonus/image_bonus.c \
				src_bonus/init_bonus.c src_bonus/utils_bonus.c src_bonus/color_bonus.c src_bonus/mouse_bonus.c \
				src_bonus/cal_bonus.c src_bonus/line_bonus.c src_bonus/list_bonus.c

OBJS        =   $(SRC:.c=.o)
BONUS_OBJS  =   $(BONUS_SRC:.c=.o)

CC          =   gcc

CFLAGS      =   -Wall -Wextra -Werror -Iincludes -Ilibft -g

MLX_FLAGS   =   -Lminilibx -lmlx -framework OpenGL -framework AppKit -lm

LIBFT_DIR   =   libft
LIBFT       =   $(LIBFT_DIR)/libft.a
LIBFT_FLAGS =   -L$(LIBFT_DIR) -lft

RM          =   rm -f

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS) $(LIBFT_FLAGS)

$(LIBFT):
	make -C $(LIBFT_DIR)

bonus: $(LIBFT) $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJS)
	$(CC) $(CFLAGS) -o $(BONUS_NAME) $(BONUS_OBJS) $(MLX_FLAGS) $(LIBFT_FLAGS)

clean:
	$(RM) $(OBJS) $(BONUS_OBJS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME) $(BONUS_NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re bonus $(LIBFT)
