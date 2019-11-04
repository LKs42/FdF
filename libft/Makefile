# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lugibone <lugibone@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/02 15:19:01 by lugibone          #+#    #+#              #
#    Updated: 2019/11/04 14:48:47 by lugibone         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

RESET = \e[0m
BOLD = \e[1m
DIM	=	\e[2m
ITALIC = \e[3m
UNDERLINE = \e[4m
BLINK = \e[5m
REVERSED = \e[7m
HIDDEN = \e[8m
DEFAULT = \e[39m
BLACK = \e[30m
RED = \e[31m
GREEN = \e[32m
YELLOW = \e[33m
BLUE = \e[34m
MAGENTA = \e[35m
CYAN = \e[36m
LIGHT_GRAY = \e[37m
DARK_GRAY = \e[90m
WHITE = \e[97m
BG_DEFAULT = \e[49m
BG_BLACK = \e[30m
BG_RED = \e[41m
BG_GREEN = \e[42m
BG_YELLOW = \e[43m
BG_BLUE = \e[44m
BG_MAGENTA = \e[45m
BG_CYAN = \e[46m
LIGHT_GRAY = \e[47m
DARK_GRAY = \e[100m
BG_WHITE = \e[107m

CCC = gcc -c
FLAGS = -Wall -Werror -Wextra
SRC_PATH = .
OBJ_PATH = .
SRC_NAME = ft_atoi.c\
	ft_bzero.c\
	ft_convert_base.c\
	ft_isalnum.c\
	ft_isalpha.c\
	ft_isascii.c\
	ft_isdigit.c\
	ft_isprint.c\
	ft_iterative_factorial.c\
	ft_iterative_power.c\
	ft_itoa.c\
	ft_lstadd.c\
	ft_lstdel.c\
	ft_lstdelone.c\
	ft_lstiter.c\
	ft_lstmap.c\
	ft_lstnew.c\
	ft_memalloc.c\
	ft_memcpy.c\
	ft_memccpy.c\
	ft_memchr.c\
	ft_memcmp.c\
	ft_memdel.c\
	ft_memmove.c\
	ft_memset.c\
	ft_putchar_fd.c\
	ft_putendl.c\
	ft_putendl_fd.c\
	ft_putchar.c\
	ft_putstr.c\
	ft_putstr_fd.c\
	ft_putnbr.c\
	ft_putnbr_fd.c\
	ft_split_char.c\
	ft_split.c\
	ft_sqrt.c\
	ft_strcat.c\
	ft_strchr.c\
	ft_strclr.c\
	ft_strcmp.c\
	ft_strcpy.c\
	ft_strdel.c\
	ft_strdup.c\
	ft_strequ.c\
	ft_striter.c\
	ft_striteri.c\
	ft_strjoin.c\
	ft_strlcat.c\
	ft_strlen.c\
	ft_strmap.c\
	ft_strmapi.c\
	ft_strncat.c\
	ft_strncmp.c\
	ft_strncpy.c\
	ft_strnequ.c\
	ft_strnew.c\
	ft_strnstr.c\
	ft_strrchr.c\
	ft_strsplit.c\
	ft_strstr.c\
	ft_strsub.c\
	ft_strtrim.c\
	ft_tolower.c\
	ft_toupper.c\
	ft_itoa_base.c\
	get_next_line.c\
	ft_str_read.c\
	ft_check_extension.c\
	ft_str_read_line.c
AR = ar rc
OBJ_NAME = $(SRC_NAME:.c=.o)

INCLUDES = includes/

all: $(NAME)

$(NAME): $(OBJ_NAME)
	@$(CCC) $(FLAGS) $(SRC_NAME) -I $(INCLUDES)
	@$(AR) $(NAME) $(OBJ_NAME)
	@ranlib $(NAME)
	@printf "$(RESET)$(BOLD)$(BG_GREEN)$(WHITE)$(DIM) DONE $(RESET)\n"
%.o: %.c
	@$(CC) -I $(INCLUDES) $(FLAGS) -c $< -o $@
	@printf "$(RESET)$(BG_GREEN) $(RESET)"
clean:
	@rm -f $(OBJ_NAME)
	@printf "$(RESET)$(BG_CYAN)$(WHITE) O_FILES CLEANED $(RESET)\n"
fclean: clean
	@rm -f $(NAME)
	@printf "$(RESET)$(BG_CYAN)$(WHITE) LIBFT.A CLEANED $(RESET) \n"
re: fclean all

.PHONY: clean fclean re
