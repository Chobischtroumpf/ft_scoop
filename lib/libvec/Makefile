# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    MAkefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/11 11:53:12 by adorigo           #+#    #+#              #
#    Updated: 2021/09/08 14:15:13 by adorigo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libvec.a

SRCS 	=	vecs.c matrices.c mat_vec3f.c mat_print.c

OBJ_DIR = ./.Objects
SRC_DIR = ./srcs
INC_DIR = ./includes

OBJS	:= $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))

CFLAGS	:= -Wall -Wextra -Werror -O3 -I$(INC_DIR)


all: CREATE_OBJDIR $(NAME)

CREATE_OBJDIR:
		@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS)
		@ar -rc $(NAME) $(OBJS)
		@ranlib $(NAME)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(INC_DIR)/libvec.h
		@gcc $(CFLAGS) -o $@ -c $<

clean:
		@rm -rf ./.Objects/$(OBJS)

fclean : clean
		@rm -f $(NAME)

re:		fclean all