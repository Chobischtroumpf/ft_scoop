# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/11 11:53:12 by adorigo           #+#    #+#              #
#    Updated: 2020/05/14 10:28:23 by adorigo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libvec.a

CFLAGS = -Wall -Wextra -Werror -I./includes -c

SRCS = mat_print.c mat_vec3f.c vecs.c matrices.c

OBJECTS = $(SRCS:%.c=%.o)


all : $(NAME) clean

$(NAME) : $(OBJECTS) 
		ar rcs $(NAME) $(OBJECTS)

$(OBJECTS) : $(SRCS)
		gcc $(CFLAGS) $(SRCS)

clean : 
	@rm -f $(OBJECTS)

fclean : clean
	@rm -f $(NAME)

re : fclean all

.PHONY: all re clean fclean
