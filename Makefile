# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nephilister <nephilister@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/21 12:30:03 by cjoanne           #+#    #+#              #
#    Updated: 2021/08/19 02:06:08 by nephilister      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	philo

SRCS_LIST	=	main.c
SRCS_DIR	=	srcs/
SRCS		=	$(addprefix $(SRCS_DIR), $(SRCS_LIST))

OBJS_LIST	=	$(SRCS_LIST:.c=.o)
OBJS_DIR	=	objects/
OBJS		=	$(addprefix $(OBJS_DIR), $(OBJS_LIST))

CC 			=	gcc
CFLAGS		=	-Wall -Wextra -Werror

INCLUDES	=	-I$(LIBFT_HEADER) -I$(HEADERS_DIR) -I$(MINILIBX_HEADERS)

HEADERS_DIR		=	./includes/
HEADERS_LIST	=	philo.h
HEADERS 		=	$(addprefix $(HEADERS_DIR), $(HEADERS_LIST))

RM	=	rm -rf

# COLORS
GREEN = \033[0;32m
BLUE= \033[0;34m
RED = \033[0;31m
RESET = \033[0m
LIBA = libft.a

all : $(NAME)

$(NAME) : $(LIBFT) $(OBJS_DIR) $(OBJS)
	@$(CC) $(OBJS) $(LIBRARIES) $(INCLUDES) -o $(NAME)
	@echo "$(NAME): $(BLUE)object files were created$(RESET)"
	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@$(CC) $(СFLAGS) $(INCLUDES) -c $< -o $@
	
$(OBJS_DIR) :
	@mkdir -p $(OBJS_DIR)
	@echo "$(NAME): $(BLUE)creating $(NAME)$(RESET)"

clean :
	@$(RM) $(OBJS_DIR)
	@$(MAKE) clean -C $(LIBFT_DIR)
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"

fclean : clean
	@$(RM) $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"

re : fclean all

.PHONY : all clean fclean re