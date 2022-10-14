# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cyelena <cyelena@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/07 20:19:07 by cyelena           #+#    #+#              #
#    Updated: 2022/10/13 20:50:39 by cyelena          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CC = cc
CFLAGS = -g -fsanitize=address
# -Wall -Wextra -Werror
RM = rm -rf

LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = minilibx/
MLX = $(MLX_DIR)/libmlx.a

SRC_DIR = src/
SRC_BONUS_DIR = src_bonus/

HEADER = inc/cub3d.h

SRC_FILES = main.c \
			parsing_utils.c \
			parsing_map.c \
			mlx_hooks.c \
			init_func.c \
			start_game.c \
			get_next_line/get_next_line.c \
			get_next_line/get_next_line_utils.c \

OBJ = $(patsubst %.c, %.o, $(addprefix $(SRC_DIR), $(SRC_FILES)))
OBJ_BONUS = $(patsubst %.c, %.o, $(addprefix $(SRC_BONUS_DIR), $(SRC_BONUS_FILES)))

all: $(LIBFT) $(MLX) $(NAME)

bonus: $(LIBFT) $(MLX)
			@make OBJ="$(OBJ_BONUS)" \
			SRC_DIR="$(SRC_BONUS_DIR)" \
			SRC_FILES="$(SRC_BONUS_FILES)" \
			HEADER="$(HEADER_BONUS)" all

$(NAME): $(OBJ) $(HEADER)
				$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit -o $@

$(SRC_DIR)%.o: $(SRC_DIR).c
					$(CC) $(CFLAGS) -Imlx -c $< -o $@

$(LIBFT):
			make -C $(LIBFT_DIR)

$(MLX):
			make -C $(MLX_DIR)


clean:
			$(RM) $(OBJ) $(OBJ_BONUS)
			make -C $(MLX_DIR) clean
			make -C $(LIBFT_DIR) clean

fclean: clean
			$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
