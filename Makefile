# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbastien <lbastien@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/10 22:10:10 by lbastien          #+#    #+#              #
#    Updated: 2023/01/23 19:11:00 by lbastien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Standard variables

NAME		=	philisophers
INCLUDE_DIR	= 	include
LIBFT		=	libft/
SRC_DIR 	=	src/
OBJ_DIR		=	obj/
CC			=	gcc
CFLAGS		=	-g -Wall -Werror -Wextra
RM			=	rm -f
AR			=	ar rcs
CMD_OUT		=	./$(NAME)

#Colors

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

#Sources

SRCS 		= 	$(wildcard $(SRC_DIR)*.c)
OBJS 		=	$(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

#exe

OBJ_F		=	.cache_exists

all:		$(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_F)
			$(CC) $(CFLAGS) -Imlx -c $< -o $@

$(NAME):	$(OBJS)
			@echo "$(CYAN)Generating libft!$(DEF_COLOR)"
			@make -C $(LIBFT)
			@$(CC) $(CFLAGS) $(OBJS) $(LIBFT)libft.a -o $(NAME)
			@echo "$(GREEN)All compiled!$(DEF_COLOR)"

$(OBJ_F):
			@mkdir -p $(OBJ_DIR)
clean:
			@$(RM) -rf $(OBJ_DIR)
			@make clean -C $(LIBFT)
			@echo "$(BLUE)Objects files cleaned!$(DEF_COLOR)"

fclean:		clean
			@make fclean -C $(LIBFT)
			@$(RM) -f $(NAME)
			@echo "$(CYAN)Executable files cleaned!$(DEF_COLOR)"

re:			fclean all
			@echo "$(GREEN)Cleaned and rebuilt everything!$(DEF_COLOR)"

norm:
	@norminette $(SRCS) $(INCLUDES) | grep -v Norme -B1 || true

.PHONY: all, clean, fclean, re, norm, out
