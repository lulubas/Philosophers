# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbastien <lbastien@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/10 22:10:10 by lbastien          #+#    #+#              #
#    Updated: 2023/01/20 18:12:35 by lbastien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Standard variables

NAME		=	libft.a
INCLUDE_DIR	= 	include
SRC_DIR 	=	src/
OBJ_DIR		=	obj/
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -D BUFFER_SIZE=1024 -I
RM			=	rm -f
AR			=	ar rcs

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

IS_DIR		=	is/
FTIS		=	ft_isalnum ft_isalpha ft_isascii ft_isdigit ft_isprint

MEM_DIR		=	mem/
FTMEM		=	ft_bzero ft_calloc ft_memchr ft_memcmp ft_memmove ft_memset \
				ft_memcpy

PUT_DIR		=	put/
FTPUT		=	ft_putchar ft_putstr ft_putnbr ft_putchar_fd ft_putendl_fd \
				ft_putnbr_fd ft_putstr_fd ft_puthex ft_putunbr

TO_DIR		=	to/
FTTO		=	ft_atoi ft_itoa ft_tolower ft_toupper

STR_DIR		=	str/
FTSTR		=	ft_split ft_strchr ft_strdup ft_striteri ft_strjoin \
				ft_strlcat ft_strlcpy ft_strlen ft_strmapi ft_strncmp \
				ft_strnstr ft_strrchr ft_strtrim ft_substr

LST_DIR		=	lst/
FTLST		=	ft_lstadd_back ft_lstadd_front ft_lstclear ft_lstdelone ft_lstiter \
				ft_lstlast ft_lstmap ft_lstnew ft_lstsize ft_intlst_addback \
				ft_intlst_addfront ft_intlst_last ft_intlst_new ft_intlst_size

PRN_DIR		=	ft_printf/
FTPRN		=	ft_printf

GNL_DIR		=	get_next_line/
FTGNL		=	get_next_line

SRC_FILES+=$(addprefix $(IS_DIR),$(FTIS))
SRC_FILES+=$(addprefix $(MEM_DIR),$(FTMEM))
SRC_FILES+=$(addprefix $(PUT_DIR),$(FTPUT))
SRC_FILES+=$(addprefix $(TO_DIR),$(FTTO))
SRC_FILES+=$(addprefix $(STR_DIR),$(FTSTR))
SRC_FILES+=$(addprefix $(LST_DIR),$(FTLST))
SRC_FILES+=$(addprefix $(PRN_DIR),$(FTPRN))
SRC_FILES+=$(addprefix $(GNL_DIR),$(FTGNL))

SRCS 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

#exei

OBJ_F		=	.cache_exists

all:		$(NAME)

$(NAME):	$(OBJS)
			@$(AR) $(NAME) $(OBJS)
			@echo "$(GREEN)Libft compiled!$(DEF_COLOR)"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c | $(OBJ_F)
			@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
			@$(CC) $(CFLAGS) $(INCLUDE_DIR) -c $< -o $@

$(OBJ_F):
			@mkdir -p $(OBJ_DIR)
			@mkdir -p $(OBJ_DIR)$(IS_DIR)
			@mkdir -p $(OBJ_DIR)$(MEM_DIR)
			@mkdir -p $(OBJ_DIR)$(PUT_DIR)
			@mkdir -p $(OBJ_DIR)$(TO_DIR)
			@mkdir -p $(OBJ_DIR)$(STR_DIR)
			@mkdir -p $(OBJ_DIR)$(LST_DIR)
			@mkdir -p $(OBJ_DIR)$(PRN_DIR)
			@mkdir -p $(OBJ_DIR)$(GNL_DIR)

clean:
			@$(RM) -rf $(OBJ_DIR)
			@$(RM) -f $(OBJ_F)
			@echo "$(BLUE)libft objects files cleaned!$(DEF_COLOR)"

fclean:		clean
			@$(RM) -f $(NAME)
			@echo "$(CYAN)libft executable files cleaned!$(DEF_COLOR)"

re:			fclean all
			@echo "$(GREEN)Cleaned and rebuilt everything for libft!$(DEF_COLOR)"

norm:
	@norminette $(SRCS) $(INCLUDES) | grep -v Norme -B1 || true

.PHONY: all, clean, fclean, re, norm
