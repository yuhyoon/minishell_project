# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/24 12:49:30 by hyeyeom           #+#    #+#              #
#    Updated: 2025/01/15 16:28:03 by hyeyeom          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

//아래는 push_swap sample
NAME		=	push_swap
INCLUDE		=	-I inc/
SRC_DIR 	=	src/
OBJ_DIR		=	obj/
CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra 
RM			=	rm -f
AR			=	ar rcs
ECHO		=	echo -e

LIBFTA		=	libft.a

OPERA_DIR	=	operation/
OPERA		=	stack_operation_push stack_operation_reverse_rotate \
				stack_operation_rotate stack_operation_swap

STACK_DIR 	=	stack/
STACK 		=	stack_set stack_sort_select stack_sort_radix \
				stack_by_hand

UTILS_DIR	=	utils/
UTILS		=	check_input free msg stack_utils

######## 제출전 삭제
TMP_DIR		=	_tmp/
TMP			=	print_arrays


SRC_FILES+=$(NAME)
SRC_FILES+=$(addprefix $(OPERA_DIR),$(OPERA))
SRC_FILES+=$(addprefix $(STACK_DIR),$(STACK))
SRC_FILES+=$(addprefix $(UTILS_DIR), $(UTILS))
## 삭제
SRC_FILES+=$(addprefix $(TMP_DIR), $(TMP))


SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

OBJF		=	.cache_exists

all:		$(NAME)

$(NAME):	$(OBJ) $(OBJF)
			$(CC) $(CFLAGS) $(OBJ) $(INCLUDE) libft.a -o $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(OBJF)
			$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJF):
			make -C libft
			cp libft/libft.a .
			mkdir -p $(OBJ_DIR)
			mkdir -p $(OBJ_DIR)$(OPERA_DIR)
			mkdir -p $(OBJ_DIR)$(STACK_DIR)
			mkdir -p $(OBJ_DIR)$(UTILS_DIR)
#src 추가되면 추가
			mkdir -p $(OBJ_DIR)$(TMP_DIR)
			touch $(OBJF)

clean:
			$(RM) -r $(OBJ_DIR)
			$(RM) $(OBJF)
			@make clean -C libft

fclean:		clean
			@make fclean -C libft
			$(RM) $(NAME) $(LIBFTA)

re:			fclean all

.PHONY:		all clean fclean re