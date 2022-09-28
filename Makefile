# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rikikyttala <rikikyttala@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/12 15:30:07 by rkyttala          #+#    #+#              #
#    Updated: 2022/09/27 12:13:59 by rikikyttala      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

S = src/corewar/
O = corewar_obj/

CORE = corewar

SRC =	$(S)main.c \
		$(S)utils.c \
		$(S)utils2.c \
		$(S)prints.c \
		$(S)parse_main_args.c \
		$(S)read_champ.c \
		$(S)sort_champs.c \
		$(S)init_game.c \
		$(S)play_game.c \
		$(S)cycle_to_die.c \
		$(S)validate_instruction.c \
		$(S)instructions1.c \
		$(S)instructions2.c \
		$(S)verbose.c \
		$(S)debug.c

OBJ = $(SRC:$S%=$O%.o)

AS = src/asm/
AO = asm_obj/

ASM = asm
ASM_SRC =	$(AS)asm.c \
			$(AS)utils.c \
			$(AS)assemble.c \
			$(AS)init.c \
			$(AS)cleanup.c \
			$(AS)read_file.c \
			$(AS)read_utils.c \
			$(AS)read_validation.c \
			$(AS)tokenization.c \
			$(AS)tokenization_utils.c \
			$(AS)tokenization_args.c \
			$(AS)tokenization_validation.c \
			$(AS)write_file.c \
			$(AS)write_header.c \
			$(AS)write_utils.c \
			$(AS)write_exec_code.c \
			$(AS)validate_labels.c

ASM_OBJ = $(ASM_SRC:$(AS)%=$(AO)%.o)

I = includes/
INC = $(I)
L = libft/
LIB = $(L)libft.a
LIBINC = $(L)$(I)

CCOMP = gcc
CFLAGS = -Wall -Wextra -Werror

.PHONY: all clean fclean re

all: $(CORE) $(ASM)

$(LIB):
	@make -C $(L)

$(AO):
	@mkdir -p $@

$(ASM_OBJ): | $(AO)

$(ASM_OBJ): $(AO)%.o: $(AS)%
	@$(CCOMP) $(CFLAGS) -c $< -o $@ -I $(INC) -I $(LIBINC)

$(ASM): $(LIB) $(ASM_OBJ)
	@echo "$(GRN)Compiling asm$(EOC)"
	$(CCOMP) $(CFLAGS) $(ASM_OBJ) $(LIB) -o $@ -I $(INC) -I $(LIBINC)
	@echo "$(GRN)asm compiled successfully$(EOC)"

$O:
	@mkdir -p $@

$(OBJ): | $O

$(OBJ): $O%.o: $S%
	@$(CCOMP) $(CFLAGS) -c $< -o $@ -I $(INC) -I $(LIBINC)

$(CORE): $(LIB) $(OBJ)
	@echo "$(GRN)Compiling corewar$(EOC)"
	$(CCOMP) $(CFLAGS) $(OBJ) $(LIB) -o $@ -I $(INC) -I $(LIBINC)
	@echo "$(GRN)corewar compiled successfully$(EOC)"


debug:
	gcc -g -fsanitize=address src/corewar/*.c libft/libft.a -I $(INC) -I $(LIBINC)

clean:
	rm -rf $(O) $(AO)

fclean: clean
	rm -f $(CORE) $(ASM)

re: fclean all

GRN = \033[0;32m
EOC = \033[0m
