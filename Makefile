# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/12 15:30:07 by rkyttala          #+#    #+#              #
#    Updated: 2022/05/10 19:15:59 by rkyttala         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

S = src/
O = obj/
I = includes/
L = libft/

SRC =	$(S)main.c \
		$(S)utils.c \
		$(S)prints.c \
		$(S)parse_main_args.c \
		$(S)read_champ.c \
		$(S)init_game.c \
		$(S)play_game.c \
		$(S)cycle_to_die.c \
		$(S)validate_instruction.c \
		$(S)instructions1.c \
		$(S)instructions2.c \
		$(S)verbose.c \
		$(S)debug.c

OBJ = $(SRC:$S%=$O%.o)
INC = $(I)
LIB = $(L)libft.a
LIBINC = $(L)$(I)

CCOMP = gcc
CFLAGS = -Wall -Wextra -Werror

NAME = corewar

.PHONY: all clean fclean re

all: $(NAME)

$O:
	@mkdir -p $@

$(OBJ): | $O

$(OBJ): $O%.o: $S%
	$(CCOMP) $(CFLAGS) -c $< -o $@ -I $(INC) -I $(LIBINC)

$(NAME): $(OBJ)
#	@make -C $(L)
#	@make -C $(L) clean
	$(CCOMP) $(CFLAGS) $^ $(LIB) -o $@ -I $(INC) -I $(LIBINC)

debug:
	gcc -g -fsanitize=address src/*.c libft/libft.a -I $(INC) -I $(LIBINC)

clean:
	rm -rf $(O)
	rm -rf a.out*

fclean: clean
	rm -f $(NAME)
	rm -f a.out

re: fclean all
