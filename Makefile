# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#  Makefile                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#  By: adorigo <alessandro.matteo.a.dorigo@ulb.be>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#  Created: 2020/04/10 13:37:24 by lorenuar            #+#    #+#              #
#  Updated: 2021/09/08 14:15:00 by adorigo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ================================ VARIABLES ================================= #

# The name of your executable
NAME	= scop

# Compiler and compiling flags
CC	= gcc
CFLAGS	= -Wall -Werror -Wextra -DGL_SILENCE_DEPRECATION=1
UNAME_S := $(shell uname -s)

# Debug, use with`make DEBUG=1`
ifeq ($(DEBUG),1)
CFLAGS	+= -g3 -fsanitize=address
endif

# Folder name
SRCDIR	= sources/
INCDIR	= -I includes/ -I lib/libft/includes -I lib/libvec/includes
ifeq ($(UNAME_S),Linux)
	INCDIR += -I /home/linuxbrew/.linuxbrew/include
endif
ifeq ($(UNAME_S), Darwin)
	INCDIR += -I ~/.brew/include/
endif

OBJDIR	= bin/

# Add include folder

CFLAGS	+= $(INCDIR)

# Linking stage flags

ifeq ($(UNAME_S),Linux)
	LDFLAGS = -L lib/libft -L lib/libvec -L /home/linuxbrew/.linuxbrew/lib -lvec -lft -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lm
endif
ifeq ($(UNAME_S),Darwin)
	LDFLAGS += -L lib/libft -L lib/libvec -L ~/.brew/lib/ -lvec -lft -lglfw -framework OpenGL 
endif

SRCS = \
	./sources/main.c					\
	./sources/utils.c					\
	./sources/parsing.c					\
	./sources/buffers_creation.c		\
	./sources/shaders/get_shaders.c		\
	./sources/matrice_manipulation.c	\
	./sources/glad.c					\
	./sources/image_loading/ppm_img.c

HEADERS = \
	./includes/scop.h\
	./includes/ppm_img.h\

# String manipulation magic
SRC		:= $(notdir $(SRCS))
OBJ		:= $(SRC:.c=.o)
OBJS	:= $(addprefix $(OBJDIR), $(OBJ))

# Colors
GR	= \033[32;1m
RE	= \033[31;1m
YE	= \033[33;1m
CY	= \033[36;1m
RC	= \033[0m

# Implicit rules
VPATH := $(SRCDIR) $(OBJDIR) $(shell find $(SRCDIR) -type d)

# ================================== RULES =================================== #

all : libft libvec $(NAME)

# Compiling
$(OBJDIR)%.o : %.c
	@mkdir -p $(OBJDIR)
	@printf "$(GR)+$(RC)"
	@$(CC) $(CFLAGS) $(CMACRO) -c $< -o $@

# Linking
$(NAME)	: $(SRCS) $(HEADERS) $(OBJS)
	@printf "\n$(GR)=== Compiled [$(CC) $(CFLAGS)] ===\n--- $(SRC)$(RC)\n"
	@$(CC) $(CFLAGS) $(CMACRO) $(OBJS) $(LDFLAGS) -o $(NAME)
	@printf "$(YE)&&& Linked [$(CC) $(LDFLAGS)] &&&\n--- $(NAME)$(RC)\n"

# Cleaning
clean :
	@make clean -C lib/libft
	@printf "$(RE)--- Removing $(OBJDIR)$(RC)\n"
	@rm -rf $(OBJDIR)


fclean : clean
	@make fclean -C lib/libft
	@make fclean -C lib/libvec
	@printf "$(RE)--- Removing $(NAME)$(RC)\n"
	@rm -f $(NAME)

libft :
	@make re -C lib/libft
	@make clean -C lib/libft

libvec :
	@make re -C lib/libvec
	@make clean -C lib/libvec
# Special rule to force to remake everything
re : fclean all

# This runs the program
run : $(NAME)
	@printf "$(CY)>>> Running $(NAME)$(RC)"
	./$(NAME)

# This specifies the rules that does not correspond to any filename
.PHONY	= all run clean fclean re libft-fclean libft-clean libft-re libft
