# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vhallama <vhallama@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/12 15:30:07 by rkyttala          #+#    #+#              #
#    Updated: 2022/05/05 16:03:04 by vhallama         ###   ########.fr        #
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
		$(S)validate_instruction.c \
		$(S)instructions1.c \
		$(S)instructions2.c

OBJ = $(SRC:$S%=$O%.o)
INC = $(I)
LIB = $(L)libft.a
LIBINC = $(L)$(I)

CCOMP = gcc
CFLAGS = -Wall -Wextra -Werror

NAME = corewar

ASM = asm
ASM_SRC =	asm.c \
			utils.c \
			assemble.c \
			init.c \
			cleanup.c \
			read_file.c \
			read_utils.c \
			read_validation.c \
			tokenization.c \
			tokenization_utils.c \
			tokenization_args.c \
			write_file.c \
			write_header.c \
			write_utils.c \
			write_exec_code.c

ASM_OBJ = $(ASM_SRC:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(ASM):
	$(CCOMP) $(CCFLAGS) -c $(addprefix src/asm/, $(ASM_SRC)) -I $(INC) -I $(LIBINC)
	$(CCOMP) $(CCFLAGS) -o $(ASM) $(ASM_OBJ) $(LIB)
	
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
	rm -rf $(O) $(ASM_OBJ)
	rm -rf a.out*

fclean: clean
	rm -f $(NAME) $(ASM)
	rm -f a.out

re: fclean all
