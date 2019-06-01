# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkozlov <vkozlov@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/03 14:46:13 by vkozlov           #+#    #+#              #
#    Updated: 2018/03/29 15:39:38 by vkozlov          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang

NAME = wolf3d

FLAGS = -Wall -Wextra -Werror -O3 

IDIR = ./include

CFLAGS = -I include \
		 -I libSDL/SDL2.framework/Headers \
		 -I libSDL/SDL2_mixer.framework/Headers/ \
		 -I libSDL/SDL2_image.framework/Headers 

LIBFT = libft

SDL2_F		= -framework SDL2 -framework SDL2_image -framework SDL2_mixer -F ./libSDL/

SDL2_P		= -rpath @loader_path/libSDL/

DIR_S = src

DIR_O = obj

HEADER = include

_DEPS = wolf.h

DEPS = $(patsubst %,$(HEADER)/%,$(_DEPS))

SOURCES =  main.c \
           handle_sdl.c \
           ray_cast.c \
		   get_next_line.c \
		   process.c \
		   text.c \
		   hookah.c \
           floor.c \
		   misc.c

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

all: obj $(NAME)

$(NAME): $(OBJS)
		make -C $(LIBFT)
		$(CC) -o $(NAME) $(OBJS) $(FLAGS)  libft/libft.a $(SDL2_P) $(SDL2_F)

obj:
		mkdir -p obj

$(DIR_O)/%.o: $(DIR_S)/%.c $(DEPS)
		$(CC) -c -o $@ $< $(FLAGS) $(CFLAGS)

norme:
		make norme -C $(LIBFT)
		echo "--------------------Checking header files wolf3d"
		norminette ./$(HEADER)
		echo "--------------------Checking source files wolf3d"
		norminette ./$(DIR_S)

clean:
		rm -f $(OBJS)
		make clean -C $(LIBFT)
		rm -rf $(DIR_O)

fclean: clean
		rm -f $(NAME)
		make fclean -C $(LIBFT)

re: fclean all

.PHONY: all, obj, norme, clean, fclean, re
.NOTPARALLEL:  all, obj, norme, clean, fclean, re
.SILENT: